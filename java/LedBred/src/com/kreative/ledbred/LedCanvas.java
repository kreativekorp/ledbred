package com.kreative.ledbred;

import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Scanner;

public class LedCanvas extends AbstractList<LedPanel> {
	private final List<LedPanel> panels = new ArrayList<LedPanel>();
	private Rectangle bounds = null;
	
	public boolean add(Scanner scan) {
		boolean changed = false;
		while (scan.hasNextInt()) {
			int x = scan.nextInt();
			if (scan.hasNextInt()) {
				int y = scan.nextInt();
				if (scan.hasNextInt()) {
					int w = scan.nextInt();
					if (scan.hasNextInt()) {
						int h = scan.nextInt();
						if (scan.hasNext()) {
							String s = scan.next();
							panels.add(new LedPanel(
								x, y, w, h,
								WindingOrder.fromString(s, WindingOrder.LTR_TTB)
							));
							changed = true;
						}
					}
				}
			}
		}
		calculateBounds();
		return changed;
	}
	
	public void clearPixels() {
		for (LedPanel panel : panels) {
			panel.clearPixels();
		}
	}
	
	public Rectangle getBounds() {
		if (bounds == null) return null;
		return new Rectangle(bounds.x, bounds.y, bounds.width, bounds.height);
	}
	
	public void paint(Graphics g, Rectangle r) {
		for (LedPanel panel : panels) {
			Rectangle pr = panel.getBounds();
			int minX = r.x + r.width * (pr.x - bounds.x) / bounds.width;
			int minY = r.y + r.height * (pr.y - bounds.y) / bounds.height;
			int maxX = r.x + r.width * (pr.x + pr.width - bounds.x) / bounds.width;
			int maxY = r.y + r.height * (pr.y + pr.height - bounds.y) / bounds.height;
			pr.setBounds(minX, minY, maxX-minX, maxY-minY);
			panel.paint(g, pr);
		}
	}
	
	public boolean setColor(Rectangle r, Point p, int color) {
		boolean changed = false;
		for (LedPanel panel : panels) {
			Rectangle pr = panel.getBounds();
			int minX = r.x + r.width * (pr.x - bounds.x) / bounds.width;
			int minY = r.y + r.height * (pr.y - bounds.y) / bounds.height;
			int maxX = r.x + r.width * (pr.x + pr.width - bounds.x) / bounds.width;
			int maxY = r.y + r.height * (pr.y + pr.height - bounds.y) / bounds.height;
			pr.setBounds(minX, minY, maxX-minX, maxY-minY);
			if (panel.setColor(pr, p, color)) changed = true;
		}
		return changed;
	}
	
	public void read(InputStream in) throws IOException {
		for (LedPanel panel : panels) panel.read(in);
	}
	
	public void write(OutputStream out) throws IOException {
		for (LedPanel panel : panels) panel.write(out);
	}
	
	public void getRGB(int[] rgb, int offset, int scan) {
		if (bounds == null) return;
		for (LedPanel panel : panels) {
			Rectangle r = panel.getBounds();
			r.x -= bounds.x;
			r.y -= bounds.y;
			panel.getRGB(rgb, offset + scan * r.y + r.x, scan);
		}
	}
	
	public void setRGB(int[] rgb, int offset, int scan) {
		if (bounds == null) return;
		for (LedPanel panel : panels) {
			Rectangle r = panel.getBounds();
			r.x -= bounds.x;
			r.y -= bounds.y;
			panel.setRGB(rgb, offset + scan * r.y + r.x, scan);
		}
	}
	
	public BufferedImage toBufferedImage(BufferedImage image, int x, int y) {
		if (bounds == null) return image;
		if (image == null) {
			image = new BufferedImage(
				x + bounds.width + x,
				y + bounds.height + y,
				BufferedImage.TYPE_INT_ARGB
			);
		}
		int[] rgb = new int[bounds.width * bounds.height];
		getRGB(rgb, 0, bounds.width);
		image.setRGB(x, y, bounds.width, bounds.height, rgb, 0, bounds.width);
		return image;
	}
	
	public void fromBufferedImage(BufferedImage image, int x, int y) {
		if (bounds == null) return;
		int[] rgb = new int[bounds.width * bounds.height];
		image.getRGB(x, y, bounds.width, bounds.height, rgb, 0, bounds.width);
		setRGB(rgb, 0, bounds.width);
	}
	
	private void calculateBounds() {
		if (panels.isEmpty()) {
			bounds = null;
		} else {
			int minX = Integer.MAX_VALUE;
			int minY = Integer.MAX_VALUE;
			int maxX = Integer.MIN_VALUE;
			int maxY = Integer.MIN_VALUE;
			for (LedPanel panel : panels) {
				bounds = panel.getBounds();
				minX = Math.min(minX, bounds.x);
				minY = Math.min(minY, bounds.y);
				maxX = Math.max(maxX, bounds.x + bounds.width);
				maxY = Math.max(maxY, bounds.y + bounds.height);
			}
			bounds = new Rectangle(minX, minY, maxX-minX, maxY-minY);
		}
	}
	
	@Override
	public boolean add(LedPanel panel) {
		if (panels.add(panel)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public void add(int index, LedPanel panel) {
		panels.add(index, panel);
		calculateBounds();
	}
	
	@Override
	public boolean addAll(Collection<? extends LedPanel> c) {
		if (panels.addAll(c)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public boolean addAll(int index, Collection<? extends LedPanel> c) {
		if (panels.addAll(index, c)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public void clear() {
		panels.clear();
		bounds = null;
	}
	
	@Override
	public boolean contains(Object o) {
		return panels.contains(o);
	}
	
	@Override
	public boolean containsAll(Collection<?> c) {
		return panels.containsAll(c);
	}
	
	@Override
	public LedPanel get(int index) {
		return panels.get(index);
	}
	
	@Override
	public int indexOf(Object o) {
		return panels.indexOf(o);
	}
	
	@Override
	public boolean isEmpty() {
		return panels.isEmpty();
	}
	
	@Override
	public int lastIndexOf(Object o) {
		return panels.lastIndexOf(o);
	}
	
	@Override
	public boolean remove(Object o) {
		if (panels.remove(o)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public LedPanel remove(int index) {
		LedPanel removed = panels.remove(index);
		calculateBounds();
		return removed;
	}
	
	@Override
	public boolean removeAll(Collection<?> c) {
		if (panels.removeAll(c)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public boolean retainAll(Collection<?> c) {
		if (panels.retainAll(c)) {
			calculateBounds();
			return true;
		}
		return false;
	}
	
	@Override
	public LedPanel set(int index, LedPanel panel) {
		LedPanel removed = panels.set(index, panel);
		calculateBounds();
		return removed;
	}
	
	@Override
	public int size() {
		return panels.size();
	}
	
	@Override
	public Object[] toArray() {
		return panels.toArray();
	}
	
	@Override
	public <T> T[] toArray(T[] a) {
		return panels.toArray(a);
	}
}
