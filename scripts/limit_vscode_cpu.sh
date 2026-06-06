#/usr/bin/bash

mkdir -p /sys/fs/cgroup/vscode_limit/
echo "800000 100000" > /sys/fs/cgroup/vscode_limit/cpu.max

get_all_subprocesses() {
    local ppid="$1"
    local sub_pids
    sub_pids="$(ps -o pid= --ppid "$ppid" 2>/dev/null)"

    for pid in $sub_pids; do
        echo "$pid"
        # 递归调用
        get_all_subprocesses "$pid"
    done
}

echo "" > /sys/fs/cgroup/vscode_limit/cgroup.procs

mainId2=$(ps axf |egrep -e 'clangd|ccls|vscode' |grep -v grep | awk '{print $1}')
DELIMITER="\n"

# 2. Split the string into an array named 'MY_ARRAY'
IFS="$DELIMITER" read -r -a MY_ARRAY <<< "$mainId2"

for p in "${MY_ARRAY[@]}"; do 
    parent_pid=$p # 替换为您的实际父进程 PID
    echo $parent_pid | tee -a /sys/fs/cgroup/vscode_limit/cgroup.procs
    my_pid_vector=( $(get_all_subprocesses "$parent_pid") )
    for i in "${my_pid_vector[@]}"; do
        echo $i | tee -a /sys/fs/cgroup/vscode_limit/cgroup.procs
    done
done

