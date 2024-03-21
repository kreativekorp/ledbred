package com.kreative.ledbred;

import javax.swing.BorderFactory;
import javax.swing.JFrame;

public class LedBredFrame extends JFrame {
	private static final long serialVersionUID = 1L;
	
	public final LedBredPanel panel;
	
	public LedBredFrame(LedPanel panel) {
		this.panel = new LedBredPanel(panel);
		this.setup();
	}
	
	public LedBredFrame(LedCanvas canvas) {
		this.panel = new LedBredPanel(canvas);
		this.setup();
	}
	
	private void setup() {
		panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
		setContentPane(panel);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setJMenuBar(new LedBredMenuBar(this));
		setResizable(false);
		setTitle("Led·Bred");
		pack();
		setLocationRelativeTo(null);
	}
}
