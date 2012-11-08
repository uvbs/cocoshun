package com.kmdsoft.mobile.ui.tree;

import java.io.Serializable;
import java.util.List;

/**
 * 树结点结构定义
 * 
 * @author Huangsy
 * 
 */
public class TreeNode implements Serializable {
	private static final long serialVersionUID = -1844948078699664527L;
	/** 结点名 */
	private String text;
	/** 结点值 */
	private String value;
	/** 扩展数据 */
	private Object extendData;

	/** 父节点 */
	private TreeNode parent;
	/** 子节点 */
	private List<TreeNode> children;

	/** 是否处于展开状态 */
	private boolean isExpanded = false;
	/** 是否显示小图标,-1表示隐藏图标 */
	private int icon = -1;
	/** 正常显示图标 */
	private int normalIcon = -1;
	/** 结点展开后的图标 */
	private int explandedIcon = -1;

	/** 是否拥有复选框 */
	private boolean hasCheckBox = false;
	/** 是否处于选中状态 */
	private boolean isChecked = false;

	/**
	 * Node构造函数
	 * 
	 * @param text
	 *            节点显示的文字
	 * @param value
	 *            节点的值
	 */
	public TreeNode(String text, String value) {
		this.text = text;
		this.value = value;
	}

	public TreeNode(String text, String value, int icon) {
		this(text, value);
		this.icon = icon;
	}

	public TreeNode(String text, String value, int icon, int explandedIcon) {
		this(text, value);
		this.icon = icon;
		this.explandedIcon = explandedIcon;
		this.normalIcon = icon;
	}

	/**
	 * 设置父节点
	 * 
	 * @param node
	 */
	public void setParent(TreeNode node) {
		this.parent = node;
	}

	/**
	 * 获得父节点
	 * 
	 * @return
	 */
	public TreeNode getParent() {
		return this.parent;
	}

	/**
	 * 设置节点文本
	 * 
	 * @param text
	 */
	public void setText(String text) {
		this.text = text;
	}

	/**
	 * 获得节点文本
	 * 
	 * @return
	 */
	public String getText() {
		return this.text;
	}

	/**
	 * 设置节点值
	 * 
	 * @param value
	 */
	public void setValue(String value) {
		this.value = value;
	}

	/**
	 * 获得节点值
	 * 
	 * @return
	 */
	public String getValue() {
		return this.value;
	}

	/**
	 * 设置节点图标文件
	 * 
	 * @param icon
	 */
	public void setIcon(int icon) {
		this.icon = icon;
	}

	/**
	 * 获得图标文件
	 * 
	 * @return
	 */
	public int getIcon() {
		return icon;
	}

	/**
	 * 是否根节点
	 * 
	 * @return
	 */
	public boolean isRoot() {
		return parent == null ? true : false;
	}

	/**
	 * 获得子节点
	 * 
	 * @return
	 */
	public List<TreeNode> getChildren() {
		return this.children;
	}

	public void setChildren(List<TreeNode> children) {
		this.children = children;
		if (children != null && !children.isEmpty())
			for (TreeNode treeNode : children) {
				treeNode.setParent(this);
			}
	}

	/**
	 * 添加子节点
	 * 
	 * @param node
	 */
	public void add(TreeNode node) {
		if (!children.contains(node)) {
			children.add(node);
			node.setParent(this);
		}
	}

	/**
	 * 清除所有子节点
	 */
	public void clear() {
		children.clear();
	}

	/**
	 * 删除一个子节点
	 * 
	 * @param node
	 */
	public void remove(TreeNode node) {
		if (!children.contains(node)) {
			children.remove(node);
		}
	}

	/**
	 * 删除指定位置的子节点
	 * 
	 * @param location
	 */
	public void remove(int location) {
		children.remove(location);
	}

	/**
	 * 获得节点的级数,根节点为0
	 * 
	 * @return
	 */
	public int getLevel() {
		return parent == null ? 0 : parent.getLevel() + 1;
	}

	/**
	 * 设置节点选中状态
	 * 
	 * @param isChecked
	 */
	public void setChecked(boolean isChecked) {
		this.isChecked = isChecked;
	}

	/**
	 * 获得节点选中状态
	 * 
	 * @return
	 */
	public boolean isChecked() {
		return isChecked;
	}

	/**
	 * 设置是否拥有复选框
	 * 
	 * @param hasCheckBox
	 */
	public void setCheckBox(boolean hasCheckBox) {
		this.hasCheckBox = hasCheckBox;
	}

	/**
	 * 是否拥有复选框
	 * 
	 * @return
	 */
	public boolean hasCheckBox() {
		return hasCheckBox;
	}

	/**
	 * 是否叶节点,即没有子节点的节点
	 * 
	 * @return
	 */
	public boolean isLeaf() {
		return children.size() < 1 ? true : false;
	}

	/**
	 * 当前节点是否处于展开状态
	 * 
	 * @return
	 */
	public boolean isExpanded() {
		return isExpanded;
	}

	/**
	 * 设置节点展开状态
	 * 
	 * @return
	 */
	public void setExpanded(boolean isExpanded) {
		this.isExpanded = isExpanded;
		if (explandedIcon != -1) {
			if (this.isExpanded) {
				this.icon = explandedIcon;
			} else if (!isExpanded) {
				this.icon = normalIcon;
			}
		}
	}

	/**
	 * 递归判断父节点是否处于折叠状态,有一个父节点折叠则认为是折叠状态
	 * 
	 * @return
	 */
	public boolean isParentCollapsed() {
		if (parent == null)
			return !isExpanded;
		if (!parent.isExpanded())
			return true;
		return parent.isParentCollapsed();
	}

	/**
	 * 递归判断所给的节点是否当前节点的父节点
	 * 
	 * @param node
	 *            所给节点
	 * @return
	 */
	public boolean isParent(TreeNode node) {
		if (parent == null)
			return false;
		if (node.equals(parent))
			return true;
		return parent.isParent(node);
	}

	public void setExplandedIcon(int explandedIcon) {
		this.explandedIcon = explandedIcon;
	}

	@Override
	public String toString() {
		return "TreeNode [text=" + text + ", value=" + value + ", extendData=" + extendData + ", parent=" + parent
		        + ", children=" + children + ", icon=" + icon + ", normalIcon=" + normalIcon + ", explandedIcon="
		        + explandedIcon + ", isChecked=" + isChecked + ", isExpanded=" + isExpanded + ", hasCheckBox="
		        + hasCheckBox + "]";
	}

}
