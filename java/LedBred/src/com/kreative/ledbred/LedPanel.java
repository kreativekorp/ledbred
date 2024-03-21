package com.kreative.ledbred;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class LedPanel {
	private final int x;
	private final int y;
	private final int width;
	private final int height;
	private final WindingOrder order;
	private final int[] pixels;
	
	public LedPanel(int x, int y, int width, int height, WindingOrder order) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.order = order;
		this.pixels = new int[width * height];
	}
	
	public void clearPixels() {
		for (int i = 0; i < pixels.length; i++) {
			pixels[i] = 0;
		}
	}
	
	public Rectangle getBounds() {
		return new Rectangle(x, y, width, height);
	}
	
	public void paint(Graphics g, Rectangle r) {
		g.setColor(Color.black);
		g.fillRect(r.x, r.y, r.width, r.height);
		for (int y = 0; y < height; y++) {
			int y1 = r.y + r.height * y / height;
			int y2 = r.y + r.height * (y+1) / height;
			for (int x = 0; x < width; x++) {
				int x1 = r.x + r.width * x / width;
				int x2 = r.x + r.width * (x+1) / width;
				int p = pixels[order.getIndex(height, width, y, x)];
				p = LedUtility.gammaCorrect(p, 0x33, 0xFF, false);
				g.setColor(new Color(p));
				g.fillOval(x1+2, y1+2, x2-x1-4, y2-y1-4);
			}
		}
	}
	
	public boolean setColor(Rectangle r, Point p, int color) {
		if (!r.contains(p)) return false;
		int x = width * (p.x - r.x) / r.width;
		int y = height * (p.y - r.y) / r.height;
		if (x < 0 || x >= width) return false;
		if (y < 0 || y >= height) return false;
		int i = order.getIndex(height, width, y, x);
		pixels[i] = ((pixels[i] == color) ? 0 : color);
		return true;
	}
	
	public void read(InputStream in) throws IOException {
		for (int i = 0; i < pixels.length; i++) {
			int b = in.read() <<  0;
			int g = in.read() <<  8;
			int r = in.read() << 16;
			int w = in.read() << 24;
			pixels[i] = w | r | g | b;
		}
	}
	
	public void write(OutputStream out) throws IOException {
		for (int p : pixels) {
			out.write(p >>  0);
			out.write(p >>  8);
			out.write(p >> 16);
			out.write(p >> 24);
		}
	}
	
	public void getRGB(int[] rgb, int offset, int scan) {
		for (int j = offset, y = 0; y < height; y++, j += scan) {
			for (int i = j, x = 0; x < width; x++, i++) {
				int p = pixels[order.getIndex(height, width, y, x)];
				p = LedUtility.gammaCorrect(p, 0, 255, false);
				rgb[i] = (0xFF << 24) | p;
			}
		}
	}
	
	public void setRGB(int[] rgb, int offset, int scan) {
		for (int j = offset, y = 0; y < height; y++, j += scan) {
			for (int i = j, x = 0; x < width; x++, i++) {
				int r = (rgb[i] >> 16) & 0xFF; r *= r; r /= 255;
				int g = (rgb[i] >>  8) & 0xFF; g *= g; g /= 255;
				int b = (rgb[i] >>  0) & 0xFF; b *= b; b /= 255;
				int p = (r << 16) | (g << 8) | (b << 0);
				pixels[order.getIndex(height, width, y, x)] = p;
			}
		}
	}
	
	public BufferedImage toBufferedImage(BufferedImage image, int x, int y) {
		if (image == null) {
			image = new BufferedImage(
				x + width + x,
				y + height + y,
				BufferedImage.TYPE_INT_ARGB
			);
		}
		int[] rgb = new int[width * height];
		getRGB(rgb, 0, width);
		image.setRGB(x, y, width, height, rgb, 0, width);
		return image;
	}
	
	public void fromBufferedImage(BufferedImage image, int x, int y) {
		int[] rgb = new int[width * height];
		image.getRGB(x, y, width, height, rgb, 0, width);
		setRGB(rgb, 0, width);
	}
}
