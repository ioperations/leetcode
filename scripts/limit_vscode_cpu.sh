#!/usr/bin/env bash

mkdir -p /sys/fs/cgroup/vscode_limit/
echo "800000 100000" >/sys/fs/cgroup/vscode_limit/cpu.max

mainId=$(ps axf | grep /opt/visual-studio-code/code | grep -v grep | head -n 1 | awk '{print $1}')

get_all_subprocesses() {
    local ppid="$1"
    local sub_pids
    sub_pids="$(ps -o pid= --ppid "$ppid" 2>/dev/null)"

    for pid in $sub_pids; do
        echo "$pid"
        get_all_subprocesses "$pid"
    done
}

parent_pid=$mainId
my_pid_vector=($(get_all_subprocesses "$parent_pid"))

echo "" >/sys/fs/cgroup/vscode_limit/cgroup.procs
for i in "${my_pid_vector[@]}"; do
    echo "$i" | tee -a /sys/fs/cgroup/vscode_limit/cgroup.procs
done
