Gesture Control Car with MPU6050 and ESP-NOW using ESP32
This project demonstrates a Gesture-Controlled Car using an MPU6050 accelerometer and gyroscope sensor for motion detection, and two ESP32 microcontrollers for wireless communication using the ESP-NOW protocol. One ESP32 reads the gestures and sends the data to the other ESP32, which controls the motors of the car accordingly.

Overview
In this project, gestures from the MPU6050 sensor mounted on a controller (held by the user) are captured and sent wirelessly using ESP-NOW to another ESP32 controlling a car's motors. The system allows the user to drive the car by tilting the controller in different directions.

Components
2 x ESP32 Development Boards
1 x MPU6050 Accelerometer & Gyroscope Sensor
1 x L298N Motor Driver (or similar motor driver)
2 x DC Motors (for driving the car)
1 x Chassis (or any car body)
Jumper wires
Breadboard
Power supply (Battery for motors)
Features
Wireless communication using ESP-NOW
Gesture-based car control with MPU6050
Real-time data transfer for responsive car movements
Low latency and robust communication
Easy-to-build hardware setup
Usage
Set up the car by connecting the receiver ESP32 to the motor driver and motors as per the circuit diagram.
Connect the MPU6050 to the transmitter ESP32 as shown in the circuit diagram.
Power both ESP32 devices (one on the car, and one for gesture control).
Control the car:
Tilt the controller forward to move the car forward.
Tilt the controller backward to move the car in reverse.
Tilt left or right to steer the car in those directions.
How It Works
MPU6050 Sensor: The sensor reads the accelerometer and gyroscope data, detecting the orientation and motion of the controller.

ESP-NOW Protocol: The transmitter ESP32 collects data from the MPU6050 and transmits it wirelessly using the ESP-NOW protocol to the receiver ESP32 on the car.

Receiver ESP32: The receiver ESP32 decodes the gesture data and sends the appropriate signals to the motor driver, which controls the car's movements.

Future Enhancements
Add speed control using gesture intensity.
Integrate additional sensors for obstacle detection (e.g., ultrasonic sensors).
Implement a mobile app for remote control.
