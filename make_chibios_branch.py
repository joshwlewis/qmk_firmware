import os
import subprocess
import sys
import re

start_commit = "fa33719adab1393753312d298b8c365e04e844b9"
core_start_commit = "455fd51a87693e8368a520730082fdc0a7c377eb"
core_branch = "qmk_chibios_core"
keyboard_branch = "qmk_chibios_keyboard"
merge_branch = "qmk_merged"
chibios_branch = "qmk_chibios"
working_dir = os.path.dirname(os.path.realpath(__file__))

def create_branch(name, start_commit):
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
            print "Cherry picking %s" % commit
            sys.stdout.flush()
            subprocess.call("git cherry-pick -X subtree=tmk_core %s" % commit)
    subprocess.call("git checkout %s" % core_branch)
    subprocess.call("git reset --hard %s" % core_start_commit)
    cherry("chibios.log")
    # Need to rebase here, so that we can cleanly merge later on
    subprocess.call("git rebase %s" % start_commit)
    # Resolve the conflict that we have
    with open("tmk_core/common/command.c", "wb+") as f:
        p = subprocess.Popen("git show 72b16683408810856e9d33b1f521ad6a15bf0699:tmk_core/common/command.c",
                             stdout=subprocess.PIPE)
        out, _ = p.communicate()
        f.write(out)
    subprocess.call("git add tmk_core/common/command.c")
    subprocess.call("git rebase --continue")
    cherry("chibios2.log")
    # We have a conflict here in README.md, which we need to resolve
    with open("tmk_core/protocol/chibios/README.md", "wb+") as f:
        p = subprocess.Popen("git show c9a56f9a8592e1389de4857a93a84a324b02e426:protocol/chibios/README.md",
                             stdout=subprocess.PIPE)
        out, _ = p.communicate()
        f.write(out)

    subprocess.call("git add tmk_core/protocol/chibios/README.md")
    subprocess.call("git cherry-pick --continue", env=get_null_edior_env())
    cherry("chibios3.log")


def cherry_pick_keyboard():
    def cherry(name):
        for commit in selected_commits(name):
            subprocess.call("git cherry-pick --no-commit %s" % commit)
            subprocess.call("git reset HEAD tmk_core/**")
            subprocess.call("git clean -d  -f -- tmk_core/**")
            subprocess.call("git checkout -- tmk_core/**")
            format = r"%an <%ae>%n%ad"
            p = subprocess.Popen("git show --format=format:\"%s\" --no-patch %s" % (format, commit),
                                 stdout=subprocess.PIPE, universal_newlines=True)
            out, _ = p.communicate()
            sys.stdout.flush()
            out = out.split("\n")
            subprocess.call("git commit --author \"%s\" --date \"%s\"" % (out[0].strip(), out[1].strip()),
                            env=get_null_edior_env())

    subprocess.call("git checkout %s" % keyboard_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    cherry("tmk_keyboard.log")


def merge_branches():
    subprocess.call("git checkout %s" % merge_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    subprocess.call("git merge %s" % core_branch, env=get_null_edior_env())
    subprocess.call("git merge %s" % keyboard_branch, env=get_null_edior_env())

def rebase_qmk_chibios():
    subprocess.call("git checkout %s" % chibios_branch)
    subprocess.call("git rebase %s" % merge_branch)

if __name__ == "__main__":
    create_branch(core_branch, core_start_commit)
    create_branch(keyboard_branch, start_commit)
    create_branch(merge_branch, start_commit)
    cherry_pick_core()
    cherry_pick_keyboard()
    merge_branches()
    rebase_qmk_chibios()
