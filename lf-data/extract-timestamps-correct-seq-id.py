import sys
import glob
import os
from enum import Enum
from collections import defaultdict

if len(sys.argv) != 2:
    print("ERROR: must specify log folder name as argument")
    exit(1)
folder_name = sys.argv[1]

f_names = glob.glob(os.path.join(folder_name, "log*.txt"))
total_diffs = []
first = 5


def get_time(line):
    start = line.find("{")
    return int(line[start+1:line.find("}", start+1)])


def is_lgsvl_published_kinematic_state(msg):
    return "Published kinematic state at:" in msg and "LGSVL" not in msg and "MPC" not in msg


def is_mpc_received_trajectory(msg):
    return "MPC received trajectory at:" in msg and "Published" not in msg and "LGSVL" not in msg


def is_lgsvl_received_vehicle_command(msg):
    return "LGSVL received vehicle command at:" in msg and "Published" not in msg and "MPC" not in msg

class Category(Enum):
    CORRUPTED = 0
    LGSVL_VSE = 1
    MPC_TRAJECTORY = 2
    LGSVL_COMMAND = 3


def find_category(msg):
    if is_lgsvl_published_kinematic_state(msg):
        return Category.LGSVL_VSE
    elif is_mpc_received_trajectory(msg):
        return Category.MPC_TRAJECTORY
    elif is_lgsvl_received_vehicle_command(msg):
        return Category.LGSVL_COMMAND
    return Category.CORRUPTED

for f_name in f_names:
    with open(f_name, "r") as f:
        print(f_name)
        yolo_lines = []
        for line in f.read().split("\n"):
            if "(YOLO)>>>" in line and line[-1] == "}" and line.count("{") == 2 and line.count("}") == 2:
                yolo_lines.append(line[line.find("(YOLO)>>>"):])
    
        yolo_lines_by_id = defaultdict(dict)
        lowest_seq_id = defaultdict(int)
        for line in yolo_lines:
            try: 
                t = line.find("{")
                t = line.find("}", t + 1)
                start = line.find("{", t + 1)
                seq_id = line[start+1:line.find("}", start+1)]
                # check that seq_id can be converted to an integer, but we still use string
                # because there are corner cases where the seq_id can be "7" but
                # corrupted as "07". 
                # In that case, we want to ignore the corner case
                int(seq_id) 
                category = find_category(line)
                if category not in yolo_lines_by_id[seq_id] and int(seq_id) > lowest_seq_id[category]:
                    lowest_seq_id[category] = int(seq_id)
                    yolo_lines_by_id[seq_id][category] = line
            except ValueError:
                pass

        diffs = []
        for seq_id in sorted(yolo_lines_by_id.keys()):
            if len(yolo_lines_by_id[seq_id]) >= 2 and \
                    Category.LGSVL_VSE in yolo_lines_by_id[seq_id] and \
                    Category.LGSVL_COMMAND in yolo_lines_by_id[seq_id] and \
                    Category.CORRUPTED not in yolo_lines_by_id[seq_id]:
                lgsvl_vse = yolo_lines_by_id[seq_id][Category.LGSVL_VSE]
                # mpc_trajectory = yolo_lines_by_id[seq_id][Category.MPC_TRAJECTORY]
                lgsvl_command = yolo_lines_by_id[seq_id][Category.LGSVL_COMMAND]
                diffs.append((get_time(lgsvl_command) - get_time(lgsvl_vse)) // 1_000_000)
        total_diffs += diffs

with open("results.txt", "w") as f:
    for i in total_diffs:
        f.write(str(i) + "\n")


with open("results.txt", "r") as f:
    s = f.read().split("\n")
    c = 0
    ave = 0
    maxi = -float('inf')
    mini = float('inf')
    for l in s:
        try:
            ave = (c * ave + int(l)) / (c + 1)
            c += 1
            maxi = max(maxi, int(l))
            mini = min(mini, int(l))
        except:
            pass
    print("Average: ", ave)
    print("Max: ", maxi)
    print("Min: ", mini)
    print("Total number of data points: ", c)
    print("Total number of runs: ", len(f_names))

import matplotlib.pyplot as plt
plt.hist(total_diffs)
plt.show()