import os
import subprocess
import sys
import re

start_commit = "fa33719adab1393753312d298b8c365e04e844b9"
core_branch = "qmk_chibios_core"
keyboard_branch = "qmk_chibios_keyboard"
merge_branch = "qmk_merged"
working_dir = os.path.dirname(os.path.realpath(__file__))

def create_branch(name):
    ret = subprocess.call("git rev-parse --verify %s" % name)
    if ret != 0:
        print "Branch %s does not exist, creating..." % name
        sys.stdout.flush()
        subprocess.call("git checkout -b %s %s" % (name, start_commit))


def selected_commits(filename):
    name = os.path.join(working_dir, filename)
    with open(name) as f:
        lines = f.readlines()

    for line in reversed(lines):
        m = re.match(r"([|/\\ *+]+)([[0-9A-Fa-f]*).*", line)
        if m.group(1).find("+") != -1 and m.group(2) != "":
            yield m.group(2)


def get_null_edior_env():
    my_env = os.environ.copy()
    my_env["GIT_EDITOR"] = "'%s'" % os.path.join(working_dir, "null_editor")
    return my_env


def cherry_pick_core():
    def cherry(name):
        for commit in selected_commits(name):
            subprocess.call("git cherry-pick -X subtree=tmk_core %s" % commit)
    subprocess.call("git checkout %s" % core_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    cherry("chibios.log")
    # We have a conflict here in README.md, which we need to resolve
    with open("tmk_core/protocol/chibios/README.md") as f:
        subprocess.call("git show c9a56f9a8592e1389de4857a93a84a324b02e426:protocol/chibios/README.md", stdout=f)

    subprocess.call("git add tmk_core/protocol/chibios/README.md")
    subprocess.call("git cherry-pick --continue", env=get_null_edior_env())
    cherry("chibios2.log")


def cherry_pick_keyboard():
    def cherry(name):
        for commit in selected_commits(name):
            subprocess.call("git cherry-pick --no-commit %s" % commit)
            subprocess.call("git reset HEAD tmk_core/**")
            subprocess.call("git clean -d  -f -- tmk_core/**")
            subprocess.call("git checkout -- tmk_core/**")
            subprocess.call("git commit", env=get_null_edior_env())

    subprocess.call("git checkout %s" % keyboard_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    cherry("tmk_keyboard.log")


def merge_branches():
    subprocess.call("git checkout %s" % merge_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    subprocess.call("git merge %s" % core_branch, env=get_null_edior_env())
    subprocess.call("git merge %s" % keyboard_branch, env=get_null_edior_env())

if __name__ == "__main__":
    create_branch(core_branch)
    create_branch(keyboard_branch)
    create_branch(merge_branch)
    cherry_pick_core()
    cherry_pick_keyboard()
    merge_branches()
