package com.kmdsoft.mobile.utils;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.Handler;
import android.os.Message;

public class TaskUtils {
	private static final String TIP_READDATA = "正在努力加载数据，请稍后...";
	private static final int MESSAGE_TASK_START = 0;
	private static final int MESSAGE_TASK_DONE = 1;

	private ExecutorService threadPool = null;
	private ProgressDialog pDialog = null;
	private Handler handler = null;
	private Context mContext;
	private Activity mActivity;

	public TaskUtils(Activity activity) {
		this.mActivity = activity;
		threadPool = Executors.newCachedThreadPool();
	}

	static class TaskResult {
		private Task task;
		private String result;

		public TaskResult(final Task task, String result) {
			super();
			this.task = task;
			this.result = result;
		}

		public Task getTask() {
			return task;
		}

		public void setTask(Task task) {
			this.task = task;
		}

		public String getResult() {
			return result;
		}

		public void setResult(String result) {
			this.result = result;
		}

	}

	/**
	 * 封装了执行简单任务与等待对话框
	 * 
	 * @param activity
	 * @param title
	 *            等待对话框标题
	 * @param message
	 *            等待对话框内容
	 * @param task
	 *            任务回调接口
	 * @param params
	 *            执行任务的参数
	 */
	public void runTaskWithWattingDialog(String title, String message, final Task task, final Task taskDone,
	        final Object... params) {
		initProgressDialog(title, message);
		threadPool.execute(new Runnable() {
			@Override
			public void run() {
				String result = task.execute(params);
				Message msg = Message.obtain();
				msg.what = MESSAGE_TASK_DONE;
				msg.obj = new TaskResult(taskDone, result);
				handler.sendMessage(msg);
			}
		});

	}

	private void initProgressDialog(String title, String message) {
		pDialog = new ProgressDialog(mActivity);
		pDialog.setTitle(title);
		pDialog.setMessage(message);
		pDialog.setCancelable(true);
		pDialog.setIndeterminate(false);
		pDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		pDialog.show();

		handler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				if (pDialog == null)
					return;

				switch (msg.what) {
				case MESSAGE_TASK_START:
					pDialog.show();
					break;
				case MESSAGE_TASK_DONE:
					if (msg != null) {
						TaskResult tr = (TaskResult) msg.obj;
						Task taskDone = tr.getTask();
						if (taskDone != null)
							taskDone.execute(tr.getResult());
					}
					pDialog.dismiss();
					break;
				default:
					break;
				}
				super.handleMessage(msg);
			}
		};
	}

	/**
	 * @see #runTaskWithWattingDialog(Activity, String, String, Task, Object...)
	 */
	public void runTaskWithWattingDialog(String message, final Task task) {
		runTaskWithWattingDialog(null, message, task, null);
	}

	/**
	 * 封装了执行简单任务与等待对话框
	 * 
	 * @see #runTaskWithWattingDialog(Activity, String, String, Task, Object...)
	 * @param activity
	 * @param task
	 * @param taskDone
	 */
	public void runTaskWithWattingDialog(final Task task, final Task taskDone) {
		runTaskWithWattingDialog(null, TIP_READDATA, task, taskDone);
	}

}
