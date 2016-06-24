import os
import subprocess
import sys
import re

start_commit = "fa33719adab1393753312d298b8c365e04e844b9"
core_branch = "qmk_chibios_core"
keyboard_branch = "qmk_chibios_keyboard"
final_branch = "qmk_chibios"
working_dir = os.path.dirname(os.path.realpath(__file__))
"""
#!/bin/bash
CHERRY="git cherry-pick -X subtree=tmk_core"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#DIR=$(echo "$DIR" | sed 's/ /\\ /g')
echo $DIR
PYTHON=/"c/python27/python"
START=fa33719adab1393753312d298b8c365e04e844b9

git rev-parse --verify qmk_chibios_core
if [ $? != 0 ]
then
git checkout -b qmk_chibios_core $START
fi

git rev-parse --verify qmk_chibios_keyboard
if [ $? != 0 ]
then
git checkout -b qmk_chibios_keyboard $START
fi

git rev-parse --verify qmk_chibios
if [ $? != 0 ]
then
git checkout -b qmk_chibios $START
fi

#git checkout qmk_chibios_core
#git reset --hard $START
#$PYTHON "$DIR/parselog.py" "$DIR/chibios.log" | xargs -t -n1 $CHERRY
#git show c9a56f9a8592e1389de4857a93a84a324b02e426:protocol/chibios/README.md > tmk_core/protocol/chibios/README.md
#git add tmk_core/protocol/chibios/README.md
#git cherry-pick --continue
#$PYTHON "$DIR/parselog.py" "$DIR/chibios2.log" | xargs -t -n1 $CHERRY

CHERRY="git cherry-pick -n"

git checkout qmk_chibios_keyboard
git reset --hard $START
REVISIONS=$(echo "$PYTHON \"$DIR/parselog.py\" \"$DIR/tmk_keyboard.log\"")
setopt shwordsplit
for x in "$(eval $REVISIONS)"; do
echo "$x"
done
#$PYTHON "$DIR/parselog.py" "$DIR/tmk_keyboard.log" | xargs -t -n1 $CHERRY

#git checkout qmk_chibios
#git reset --hard $START
#git merge qmk_chibios_core
"""


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
    my_env = os.environ.copy()
    my_env["GIT_EDITOR"] = "'%s'" % os.path.join(working_dir, "null_editor")
    subprocess.call("git cherry-pick --continue", env=my_env)
    cherry("chibios2.log")


def cherry_pick_keyboard():
    def cherry(name):
        for commit in selected_commits(name):
            subprocess.call("git cherry-pick --no-commit %s" % commit)
            subprocess.call("git reset HEAD tmk_core/**")
            subprocess.call("git clean -d  -f -- tmk_core/\\*\\*")
            subprocess.call("git checkout tmk_core/\\*\\*")
            my_env = os.environ.copy()
            my_env["GIT_EDITOR"] = "'%s'" % os.path.join(working_dir, "null_editor")
            subprocess.call("git commit", env=my_env)

    subprocess.call("git checkout %s" % keyboard_branch)
    subprocess.call("git reset --hard %s" % start_commit)
    cherry("tmk_keyboard.log")

if __name__ == "__main__":
    create_branch(core_branch)
    create_branch(keyboard_branch)
    create_branch(final_branch)
    #cherry_pick_core()
    cherry_pick_keyboard()
