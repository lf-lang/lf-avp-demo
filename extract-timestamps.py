f_name = input("file name: ")

trajectories = []
kinematic = []

with open(f_name, "r") as f:
    for line in f.read().split("\n"):
        if "(YOLO)>>> MPC received" in line:
            trajectories.append(line)
        elif "(YOLO)>>> Published kinematic" in line:
            kinematic.append(line)

diffs = []
for i, j in zip(trajectories, kinematic):
    i_l = i.find("{")
    traj_t = int(i[i_l + 1:i.find("}", i_l + 1)])
    j_l = j.find("{")
    kine_t = int(j[j_l + 1:j.find("}", j_l + 1)])
    diffs.append(traj_t - kine_t)

print(diffs)