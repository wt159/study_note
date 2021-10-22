#git常用命令
##版本回滚
###本地仓库回退
1. 回退到上个版本
    ```git
    git  reset  --hard  HEAD^
    ```
2. 回退到上上个版本
    ```git
    git  reset  --hard  HEAD^^
    ```
2. 回退到前N个版本
    ```git
    git  reset  --hard  HEAD~N
    ```
3. 回退到指定commit
    ```git
    git  reset  --hard  [commit-id]
    ```
##删除分支
1. 删除远端仓库分支
    ```git
    git push origin --delete [branch-name]
    ```
2. 删除本地仓库分支
    ```git
    git branch -D [branch-name]
    ```
###账户配置

###常见问题
1.本地分支和远端分支有着不同版本 `fatal: refusing to merge unrelated histories`
    ```git
    git pull origin master --allow-unrelated-histories
    ```
2. 