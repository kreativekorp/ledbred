package com.kreative.ledbred;

import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.swing.JComponent;

public class LedComponent extends JComponent {
	private static final long serialVersionUID = 1L;
	
	private LedCanvas canvas;
	private int color = -1;
	private Dimension minSize = null;
	private Dimension prefSize = null;
	
	public LedComponent(LedPanel panel) {
		this.canvas = new LedCanvas();
		this.canvas.add(panel);
		this.setup();
	}
	
	public LedComponent(LedCanvas canvas) {
		this.canvas = canvas;
		this.setup();
	}
	
	public void setPanel(LedPanel panel) {
		this.canvas = new LedCanvas();
		this.canvas.add(panel);
		this.repaint();
	}
	
	public void setCanvas(LedCanvas canvas) {
		this.canvas = canvas;
		this.repaint();
	}
	
	public LedPanel getPanel() {
		return (canvas.size() == 1) ? canvas.get(0) : null;
	}
	
	public LedCanvas getCanvas() {
		return canvas;
	}
	
	public void clearPixels() {
		canvas.clearPixels();
		repaint();
	}
	
	public boolean openPicture(File file) {
		if (Main.openPicture(canvas, file)) {
			repaint();
			return true;
		}
		return false;
	}
	
	public boolean savePicture(File file) {
		return Main.savePicture(canvas, file);
	}
	
	public boolean importPicture(File file) {
		if (Main.importPicture(canvas, file)) {
			repaint();
			return true;
		}
		return false;
	}
	
	public boolean exportPicture(File file) {
		return Main.exportPicture(canvas, file);
	}
	
	public boolean copyPicture() {
		BufferedImage image = canvas.toBufferedImage(null, 0, 0);
		if (image == null) return false;
		ImageSelection sel = new ImageSelection(image);
		Clipboard cb = Toolkit.getDefaultToolkit().getSystemClipboard();
		cb.setContents(sel, sel);
		return true;
	}
	
	public boolean pastePicture() {
		Rectangle bounds = canvas.getBounds();
		if (bounds == null) return false;
		Clipboard cb = Toolkit.getDefaultToolkit().getSystemClipboard();
		if (!cb.isDataFlavorAvailable(DataFlavor.imageFlavor)) return false;
		try {
			Image original = (Image)cb.getData(DataFlavor.imageFlavor);
			if (original == null) return false;
			BufferedImage rendered = LedUtility.toBufferedImage(original);
			if (rendered == null) return false;
			BufferedImage scaled = new BufferedImage(bounds.width, bounds.height, BufferedImage.TYPE_INT_ARGB);
			Graphics2D g = scaled.createGraphics();
			g.drawImage(rendered, 0, 0, bounds.width, bounds.height, null);
			g.dispose();
			canvas.fromBufferedImage(scaled, 0, 0);
			repaint();
			return true;
		} catch (Exception e) {
			return false;
		}
	}
	
	public int getSelectedColor() {
		return color;
	}
	
	public void setSelectedColor(int color) {
		this.color = color;
	}
	
	public Dimension getMinimumSize() {
		if (minSize != null) return minSize;
		Insets insets = getInsets();
		Rectangle r = canvas.getBounds();
		int w = (r == null) ? (insets.left + insets.right) : (r.width * 12 + insets.left + insets.right);
		int h = (r == null) ? (insets.top + insets.bottom) : (r.height * 12 + insets.top + insets.bottom);
		return new Dimension(w, h);
	}
	
	public void setMinimumSize(Dimension d) {
		this.minSize = d;
	}
	
	public Dimension getPreferredSize() {
		if (prefSize != null) return prefSize;
		Insets insets = getInsets();
		Rectangle r = canvas.getBounds();
		int w = (r == null) ? (insets.left + insets.right) : (r.width * 24 + insets.left + insets.right);
		int h = (r == null) ? (insets.top + insets.bottom) : (r.height * 24 + insets.top + insets.bottom);
		return new Dimension(w, h);
	}
	
	public void setPreferredSize(Dimension d) {
		this.prefSize = d;
	}
	
	protected void paintComponent(Graphics g) {
		if (g instanceof Graphics2D) {
			((Graphics2D)g).setRenderingHint(
				RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON
			);
		}
		Insets insets = getInsets();
		int x = insets.left;
		int y = insets.top;
		int w = getWidth() - insets.right - insets.left;
		int h = getHeight() - insets.bottom - insets.top;
		Rectangle r = new Rectangle(x, y, w, h);
		canvas.paint(g, r);
	}
	
	private void setup() {
		this.setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				Insets insets = getInsets();
				int x = insets.left;
				int y = insets.top;
				int w = getWidth() - insets.right - insets.left;
				int h = getHeight() - insets.bottom - insets.top;
				Rectangle r = new Rectangle(x, y, w, h);
				int mx = e.getX() - insets.left;
				int my = e.getY() - insets.top;
				Point p = new Point(mx, my);
				if (canvas.setColor(r, p, color)) {
					repaint();
				}
			}
		});
	}
}
