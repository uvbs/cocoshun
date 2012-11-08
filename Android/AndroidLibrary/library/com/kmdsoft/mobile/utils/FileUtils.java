package com.kmdsoft.mobile.utils;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * 文件操作工具
 * 
 * @author Huangsy
 * 
 */
public class FileUtils {
	private final static int BUFFER_SIZE = 1024;

	public static void copyFile(InputStream in, OutputStream out) throws Exception {
		copyFile(in, out, true);
	}

	/**
	 * 
	 * @param in
	 * @param out
	 * @param bInnerClose 是否在方法内部就关闭流
	 * @throws Exception
	 */
	public static void copyFile(InputStream in, OutputStream out, boolean bInnerClose) throws Exception {
		try {
			int length = in.available();
			int len = (length % BUFFER_SIZE == 0) ? (length / BUFFER_SIZE) : (length / BUFFER_SIZE + 1);
			byte[] temp = new byte[1024];
			for (int i = 0; i < len; i++) {
				in.read(temp);
				out.write(temp);
			}
		} finally {
			try {
				if (bInnerClose && in != null)
					in.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			try {
				if (bInnerClose && out != null)
					out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static void copyFile(String fileFromPath, String fileToPath) throws Exception {
		InputStream in = null;
		OutputStream out = null;
		try {
			in = new FileInputStream(fileFromPath);
			out = new FileOutputStream(fileToPath);
			copyFile(in, out, false);
		} finally {
			try {
				if (in != null)
					in.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			try {
				if (out != null)
					out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
