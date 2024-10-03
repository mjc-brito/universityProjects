# Power Electronics and Drives

This repository contains two assignments for the course in Power Electronics and Drives, part of the Master's program in Electrical and Computer Engineering. 

## Repository Contents

### EPA Trabalho1

The assignment described in the document is focused on the study, design, and experimental evaluation of a controlled AC-DC bridge rectifier. The rectifier is powered by a sinusoidal AC source with a 12V effective value at 50Hz frequency. The load is a purely resistive 10Ω component. The key objectives include:

    System Design: Dimensioning the rectifier components, assuming ideal diodes and thyristors, with specific parameters such as firing angles, ripple voltage, and current limits.

    Simulation: Modeling the system in Simulink to validate its performance under forced conditions, using Fourier series approximations and analyzing the output waveforms.

    Component Selection: Choosing appropriate diodes and thyristors based on the circuit's requirements, including factors like current and voltage ratings.

    Analysis: The report also addresses challenges like managing initial current spikes, where inductors and capacitors are proposed to reduce peak currents and stabilize the output.

The project includes both theoretical calculations and practical simulations, with MATLAB code used to calculate and plot the current and voltage waveforms of the system.

### EPA Trabalho2

The assignment described in the document involves the implementation of a single-phase, controlled AC-DC bridge rectifier. The project includes the design, hardware assembly, software programming, and experimental evaluation of the rectifier. Key objectives include:

    1. Introduction: The rectifier is powered by a 12V, 50Hz sinusoidal AC source, and the load is a 10Ω resistive component. The project aims to control the power delivered to the load by adjusting the firing angle of the thyristors.

    2. Development:
        - Hardware: The rectifier circuit consists of four parts—firing angle control via a potentiometer, a bridge rectifier, a filtering circuit, and the resistive load.
        Software: Arduino code was developed to calculate the firing angle based on the potentiometer position and control the firing of the thyristors. The firing is synchronized with the AC waveform to adjust power delivery based on the firing angle, ranging from 0° to 180°.

        - Experimental Results: The experimental phase involved testing the rectifier circuit with various firing angles. The voltage and current waveforms at different firing angles were analyzed to observe how the output power varied with the angle.

    3. Conclusion: The results showed that as the firing angle increased, the average voltage delivered to the load decreased, allowing for effective control of power delivery. This system could be used for applications like heaters or ovens, where controlling the power is essential.

The report also includes Arduino code used for controlling the thyristors and managing the zero-crossing detection to ensure synchronization with the AC signal

## Authors

- **Matheus José Cáceres Brito** (57003)
- **Joaquim Lopes** (58182)
- **Simão Costa** (56810)
- **Diogo Delgado** (64062)

## Institution

Department of Electrical and Computer Engineering (DEEC), NOVA School of Science and Technology (NOVA-FCT).