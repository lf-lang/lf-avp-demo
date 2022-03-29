import sys
import glob
# if len(sys.argv) != 2:
#     print("ERROR: must specify log file name as argument")
#     exit(1)
# f_name = sys.argv[1]

f_names = glob.glob("lf-data/log*.txt")

first = 5
total_diffs = []

for f_name in f_names:
    with open(f_name, "r") as f:
        print(f_name)
        trajectories = []
        kinematic = []
        seen_route = False
        for line in f.read().split("\n"):
            if not seen_route and "Received route" in line:
                seen_route = True
            if seen_route and "(YOLO)>>> M" in line:
                trajectories.append(line)
            elif seen_route and "(YOLO)>>> P" in line:
                kinematic.append(line)
        diffs = []
        for i, j in zip(trajectories[1:first+1], kinematic[1:first+1]):
            i_l = i.find("{")
            traj_t = int(i[i_l + 1:i.find("}", i_l + 1)])
            j_l = j.find("{")
            kine_t = int(j[j_l + 1:j.find("}", j_l + 1)])
            diffs.append((traj_t - kine_t) // 1_000_000)
        print(diffs)
        total_diffs += diffs

with open("results.txt", "w") as f:
    for i in total_diffs:
        f.write(str(i) + "\n")
