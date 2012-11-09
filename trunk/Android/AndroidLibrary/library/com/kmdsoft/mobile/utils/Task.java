package com.kmdsoft.mobile.utils;

/**
 * 任务回调接口</br>
 * 
 * @see TaskUtils#runTaskWithWattingDialog(String, Task)
 * @author Huangsy
 * 
 */
public interface Task {
    /**
     * 回调任务
     * @param result 任务
     * @param params 任务参数
     * @return 返回到下一步任务
     */
    public String execute(Object result, Object... params);
}
