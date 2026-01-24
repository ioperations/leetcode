#!/usr/bin/env python3
import threadpool
import subprocess


def fill_in_python_command() -> dict:
    url: dict = {
        "httpie": "https://github.com/httpie/httpie.git",
        "curlie": "https://github.com/rs/curlie.git",
    }
    return url


def fill_in_go_command() -> dict:
    url: dict = {
        "duf": "https://github.com/dandavison/delta.git",
        "fzf": "https://github.com/junegunn/fzf.git",
    }
    return url


def fill_in_rust_command() -> dict:
    url: dict = {
        "grex": "https://github.com/pemistahl/grex.git",
        "nu": "https://github.com/nushell/nushell.git",
        "bat": "https://github.com/sharkdp/bat.git",
        "lsd": "https://github.com/Peltoche/lsd.git",
        "dust": "https://github.com/bootandy/dust.git",
        "delta": "https://github.com/dandavison/delta.git",
        "ripgrep": "https://github.com/BurntSushi/ripgrep.git",
        "fd": "https://github.com/sharkdp/fd.git",
        "broot": "https://github.com/Canop/broot.git",
        "rustscan": "https://github.com/RustScan/RustScan",
        "zoxide":"https://github.com/ajeetdsouza/zoxide",
        "dog":"https://github.com/ogham/dog",
        "xh":"https://github.com/ducaale/xh",
        # "curlie":"https://github.com/rs/curlie",
        "procs":"https://github.com/dalance/procs",
        "gping":"https://github.com/orf/gping",
        "hyperfile":"https://github.com/sharkdp/hyperfine",
        "sd":"https://github.com/chmln/sd",
        "fd":"https://github.com/sharkdp/fd",
        "dust":"https://github.com/bootandy/dust",
        "exa":"https://github.com/ogham/exa",
        "rga":"https://github.com/phiresky/ripgrep-all",
    }

    return url


def install_go_command(cmd: str):
    subprocess.run("go get -u {0}".format(cmd.split(5, -1)))


def install_rust_command(command :str , giturl: str):
    subprocess.run(
        ["cargo", "install", "--force", "--git", giturl, "--bin", command])


def myprint(h):
    print("print on ")
    print(h)


def dict_to_list(d: dict) -> list:
    l = []
    for key in d:
        l.append(d[key])
    return l

def dict_to_list_rust(d: dict) -> list:
    l = []
    for key in d:
        l.append([key , d[key]])
    return l



def main():
    """
    FIXME: the doc
    Help function to create entry point
    """
    pool = threadpool.ThreadPool(16)
    # request = threadpool.makeRequests(myprint, [1, 2, 3])
    dict_rust = fill_in_rust_command()
    list_rust = dict_to_list_rust(dict_rust)
    fun_var = []
    for k in list_rust:
        fun_var.append((k,None))

    request = threadpool.makeRequests(install_rust_command, fun_var)
    print(list_rust)
    [pool.putRequest(req) for req in request]
    # [pool.putRequest(req) for req in request]
    pool.wait()


if __name__ == "__main__":
    main()
