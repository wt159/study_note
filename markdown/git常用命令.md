#git常用命令
[toc]
##基本操作
1. 建立本地仓库
    ```git
    git  init
    ```
2. 本地仓库和远端仓库相关联
    ```git
    git  remote add origin <git地址>
    ```
3. 查看当前版本与上个版本的不同
    ```git
    git  diff <file_name>
    ```
4. 查看当前仓库的配置信息(用户名、邮箱等)
    ```git
    git  config --list
    ```
5. 查看状态
    ```git
    git  status
    ```
6. 查看提交历史
    ```git
    git  log --oneline
    ```
7. 查看本地操作记录
    ```git
    git  reflog
    ```
##代码下载
1. 下载源码
    ```git
    git  clone <git地址>
    ```
2. 切换到开发分支
    ```git
    git checkout <master>
    ```
3. 更新代码
    ```git
    git fetch
    git pull
    ```
4. 在本地新建分支并关联到远端issue创建的分支
    ```git
    git checkout -b "new-fix_branch" "origin/remote-fix-branch"
    ```
##代码提交
1. 添加到本地暂存库
    ```git
    git  add  <file_name>
    ```
2. 提交到本地仓库
    ```git
    git  commit -m "modify_info"
    ```
3. 提交到远端仓库
    ```git
    git  push origin <remote_branch>
    ```
##版本回滚
###已修改文件(未暂存)
1. 撤销 所有已修改但未放入暂存区的文件，但不包括新增的文件
    ```git
    git  checkout .
    git  checkout -- .
    ```
2. 撤销指定文件的修改
    ```git
    git  checkout <file_name>
    git  checkout -- <file_name>
    ```
###已暂存文件(未commit)
1. 撤销 已暂存文件，使其重新放回工作区,变为已修改文件
    ```git
    git  reset  HEAD <file_name>
    ```
###已commit文件(本地仓库回退)
1. 查看commit-id
    ```git
    git  reflog
    git log --oneline
    ```
2. 回退到上个版本
    ```git
    git  reset  --hard  HEAD^
    ```
3. 回退到上上个版本
    ```git
    git  reset  --hard  HEAD^^
    ```
4. 回退到前N个版本
    ```git
    git  reset  --hard  HEAD~N
    ```
5. 回退到指定commit
    ```git
    git  reset  --hard  [commit-id]
    ```
###合并本地多个commit
详情见：[Git合并多个commit,保持历史简洁](https://cloud.tencent.com/developer/article/1690638)
1. 从最新版本(HEAD)开始往过去数3个版本
    ```git
    git rebase -i HEAD~3
    ```
2. 合并指定版本号(不包含此版本)
    ```git
    git rebase -i <commit_id>
    ```
##分支管理
1. 创建本地分支
    ```git
    git branch [new-branch-name]
    ```
2. 创建分支并切换到新分支
    ```git
    git checkout -b [new-branch-name]
    ```
3. 查看本地分支
    ```git
    git branch
    ```
4. 查看远端分支
    ```git
    git branch -r
    ```
5. 查看所有分支
    ```git
    git branch -a
    ```
6. 切换分支
    ```git
    git checkout [branch-name]
    ```
7. 删除远端仓库分支
    ```git
    git push origin --delete [branch-name]
    ```
8. 删除本地仓库分支
    ```git
    git branch -D [branch-name]
    ```
##账户配置

##常见问题
1.本地分支和远端分支有着不同版本 `fatal: refusing to merge unrelated histories`
    ```git
    git pull origin master --allow-unrelated-histories
    ```
2. 