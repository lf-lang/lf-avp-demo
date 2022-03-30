import sys
import glob
# if len(sys.argv) != 2:
#     print("ERROR: must specify log file name as argument")
#     exit(1)
# f_name = sys.argv[1]

f_names = glob.glob("log*.txt")
total_diffs = []
first = 5

def get_time(line):
    start = line.find("{")
    return int(line[start+1:line.find("}", start+1)])


for f_name in f_names:
    with open(f_name, "r") as f:
        print(f_name)
        yolo_lines = []
        for line in f.read().split("\n"):
            if "(YOLO)>>>" in line and line[-1] == "}" and line.count("{") == 2 and line.count("}") == 2:
                yolo_lines.append(line[line.find("(YOLO)>>>"):])
        

        yolo_lines_by_id = {}
        for line in yolo_lines:
            try: 
                t = line.find("{")
                t = line.find("}", t + 1)
                start = line.find("{", t + 1)
                seq_id = int(line[start+1:line.find("}", start+1)])
                if seq_id not in yolo_lines_by_id:
                    yolo_lines_by_id[seq_id] = []
                yolo_lines_by_id[seq_id].append(line)
            except:
                pass

        diffs = []
        for seq_id in sorted(yolo_lines_by_id.keys()):
            if len(yolo_lines_by_id[seq_id]) == 3:
                # print(yolo_lines_by_id[seq_id])
                lgsvl_kms, mpc_trajectory, lgsvl_command = sorted(yolo_lines_by_id[seq_id])[::-1]
                diffs.append((get_time(lgsvl_command) - get_time(lgsvl_kms)) // 1_000_000)
                if diffs[-1] < 0:
                    print(sorted(yolo_lines_by_id[seq_id]))
        total_diffs += diffs

with open("results.txt", "w") as f:
    for i in total_diffs:
        f.write(str(i) + "\n")


# with open("results.txt", "r") as f:
#     s = f.read().split("\n")
#     c = 0
#     ave = 0
#     maxi = -float('inf')
#     mini = float('inf')
#     for l in s:
#         try:
#             ave = (c * ave + int(l)) / (c + 1)
#             c += 1
#             maxi = max(maxi, int(l))
#             mini = min(mini, int(l))
#         except:
#             pass
#     print("Average: ", ave)
#     print("Max: ", maxi)
#     print("Min: ", mini)