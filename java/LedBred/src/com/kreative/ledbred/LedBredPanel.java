package com.kreative.ledbred;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JPanel;

public class LedBredPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	
	public final LedComponent leds;
	public final ColorSelector colors;
	
	public LedBredPanel(LedPanel panel) {
		this.leds = new LedComponent(panel);
		this.colors = new ColorSelector(leds);
		this.setup();
	}
	
	public LedBredPanel(LedCanvas canvas) {
		this.leds = new LedComponent(canvas);
		this.colors = new ColorSelector(leds);
		this.setup();
	}
	
	private void setup() {
		setLayout(new BorderLayout(12, 12));
		add(horizontalCenter(size(leds)), BorderLayout.CENTER);
		add(colors, BorderLayout.PAGE_END);
	}
	
	private static JPanel horizontalCenter(Component c) {
		JPanel p = new JPanel();
		p.setLayout(new BoxLayout(p, BoxLayout.LINE_AXIS));
		p.add(Box.createHorizontalGlue());
		p.add(c);
		p.add(Box.createHorizontalGlue());
		return p;
	}
	
	private static <C extends JComponent> C size(C c) {
		Dimension d = c.getPreferredSize();
		c.setMinimumSize(d);
		c.setPreferredSize(d);
		c.setMaximumSize(d);
		return c;
	}
}
