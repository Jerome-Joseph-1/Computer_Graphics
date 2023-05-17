# Git Workflow

This repository follows a specific Git workflow. Please refer to the following instructions for a successful workflow.

## Syncing with Remote Repository

Before starting any development work, ensure that your main branch is in sync with the remote repository (upstream). Run the following command to get the latest updates:

```git pull upstream main```


## Creating a New Feature Branch

If you want to develop a new feature, first create a new branch based on the main branch. Use the following command to create and switch to the new branch:

```git checkout -b branch-name```


To list all available branches, use the command:

```git branch```


## Adding Functionalities and Committing Changes

Once you have created and switched to your feature branch, start adding the desired functionalities. After making changes, commit them using the following commands:

```git add .```

```git commit -m "message" ```


## Syncing Main Branch with Remote Repository

To keep your main branch up to date with the remote repository, switch back to the main branch and sync it with the upstream main branch:

```git checkout main```

```git pull upstream main```


## Rebasing the Feature Branch

After syncing the main branch, switch back to your feature branch and rebase it with the main branch to incorporate the latest changes:

```git checkout branch-name```

```git rebase main```


If any issues occur during the rebase, resolve them and commit the changes using the commands:

```git add .```

```git commit -m "message"```


To continue with the rebase process, use the command:
```git rebase --continue ```


Resolve any subsequent issues that may arise.

## Pushing the Feature Branch

Once your feature branch is in sync with the remote repository and includes all the implemented features, push the branch to your repository using the command:

```git push origin branch-name```


## Opening a Pull Request

Finally, go to [github.com](https://github.com) and open a pull request to merge your feature branch into the main branch.


