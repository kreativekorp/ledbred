package com.kreative.ledbred;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.Polygon;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

public class ColorSelector extends JPanel {
	private static final long serialVersionUID = 1L;
	
	public static final List<Integer> COLORS = Collections.unmodifiableList(
		Arrays.asList(new Integer[] {
			0,        // black
			0x222222, // dark gray
			0x666666, // gray
			-1,       // white
			0xFFFF00, // yellow
			0xFF6600, // orange
			0xFF0000, // red
			0xFF00FF, // pink
			0x6600FF, // purple
			0x0000FF, // blue
			0x00FFFF, // cyan
			0x00FF66, // aqua
			0x00FF00, // green
			0x002200, // dark green
			0x996633, // tan
			0x332211, // brown
		})
	);
	
	public ColorSelector(final LedComponent c) {
		super(new GridLayout(1, 0, 1, 1));
		ButtonGroup group = new ButtonGroup();
		for (final int color : COLORS) {
			JToggleButton b = square(new JToggleButton(colorIcon(color)));
			b.setSelected(c.getSelectedColor() == color);
			add(b);
			group.add(b);
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					c.setSelectedColor(color);
				}
			});
		}
	}
	
	private static final Polygon PEG = new Polygon(
		new int[] { 0, 0, 3, 3, 10, 14, 21, 21, 24, 24 },
		new int[] { 24, 12, 12, 6, 0, 0, 6, 12, 12, 24 },
		10
	);
	
	private static ImageIcon colorIcon(int color) {
		BufferedImage image = new BufferedImage(24, 24, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g = image.createGraphics();
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g.setColor(new Color(LedUtility.gammaCorrect(color, 0, 255, false)));
		g.fill(PEG);
		g.dispose();
		return new ImageIcon(image);
	}
	
	private static <C extends JComponent> C square(C c) {
		Dimension d = c.getPreferredSize();
		d.width = (d.height += 8);
		c.setMinimumSize(d);
		c.setPreferredSize(d);
		c.setMaximumSize(d);
		c.putClientProperty("JButton.buttonType", "bevel");
		return c;
	}
}
