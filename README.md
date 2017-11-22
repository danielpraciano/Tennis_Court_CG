# Tennis_Court_CG
  Project to model a tennis court using computer graphics' techniques.

# How to use in Debian:
  - Install some compiler for C++14 (g++ 6.3.0 or newer)
  - Install Qt Creator 4.2.0 or newer
  - Install armadillo, openblas and laplack
  - Install glut, glu and openGL
  
  - Open Qt Creator and "Open Project"
  - Select this project
  - Configure path to builds (release and debug)
  
  - Have fun!

# Workflow to develop:
1. Starting the development
  $ git checkout master
  $ git pull

2. Creating a new work branch
  $ git checkout –b <work_branch>

3. Getting a updates from remote master
  $ git checkout master
  $ git pull

4. Rebasing work branch
  $ git checkout <work_branch>
  $ git rebase master

5. Merging
  $ git checkout master
  $ git merge <work_branch>

6. Pushing
  $ git push origin master
