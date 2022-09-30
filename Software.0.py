from xml.etree.ElementTree import TreeBuilder
import pygame
from socket import *
import time 
import json, os 
#please make sure you cd into the directory where ps4_keys.json is saved or edit the file accordingly to match the path where ps4_keys.json is saved
with open(os.path.join("ps4_keys.json"),'r+') as file:
    button_keys = json.load(file)
analog_keys={0:0, 1:0, 2:0, 3:0, 4:-1, 5:-1}
### Json file shows which buttons are mapped to which number on pygames
### It will be included in the software branch
#make sure you cd into the directoy where the json file is saved or include the path in the os.path.join command

#Setting up UDP connection to arduino board
address= ('192.168.1' , 5000) #Please note I do not have a physical board so i dont know what to put here
client_socket = socket (AF_INET, SOCK_DGRAM)
client_socket.settimeout(2) #wait 2 second for response

pygame.init()
pygame.joystick.init()
joysticks=[pygame.joystick.Joystick(x) for x in range (pygame.joystick.get_count())] #adding the all the joysticks to a list
#initializing all the joysticks for use 
for joystick in joysticks:
    joystick.init()
#opening a window so python can read my inputs 

screen = pygame.display.set_mode([100,200])


#the controls are based off ps4 controller
#buttons will be mapped to using the arm commands and led lights
#the analog input will be used to guide the motion of the rover
while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == button_keys['left_arrow']:
                data = "ArmCommand_upperExtender"
                print(data)
                client_socket.sendto (data , address)
            if event.button == button_keys['right_arrow']:
                data = "ArmCommand_lowerExtender"
                client_socket.sendTo (data, address)
                print(data)
            if event.button == button_keys['down_arrow']:
                data = "ArmCommand_screwDriver"
                print(data)
                client_socket.sendTo (data, address)
            if event.button == button_keys['up_arrow']:
                data= "ArmCommand_claw"
                print(data)
                client_socket.sendTo (data, address)
            if event.button == button_keys['triangle']:
                data= "ArmCommand_hoist"
                print(data)
                client_socket.sendTo (data, address)
            if event.button == button_keys['circle']:
                data= "ArmCommand_swivel"
                print(data)
                client_socket.sendTo (data, address)
            if event.key == pygame.K_q:
                pygame.quit()
            #Python will read the user's joystick input then send a packet according to the input
            #if joystick points forward:
                #send drive command to move the rover forward
            if event.type == pygame.JOYAXISMOTION:
                analog_keys[event.axis] = event.value
                # print(analog_keys)
                # Horizontal Analog
                if abs(analog_keys[0]) > .4:
                    if analog_keys[0] < -.7:
                        data="DriveCommand_leftWheel1_leftWheel2_leftWheel3"
                        print(data)
                        client_socket.sendTo (data, address)
                    if analog_keys[0] > .7:
                        data="DriveCommand_righWheel1_rightWheel2_rightWheel3"
                        print(data)
                        client_socket.sendTo (data, address)
                # Vertical Analog
                if abs(analog_keys[1]) > .4:
                    if analog_keys[1] < -.7:
                        data="DriveCommand_leftWheel1_rightWheel1_leftWheel2_rightWheel2_leftWheel3_rightWheel3_forward"
                        print(data)
                        client_socket.sendTo (data, address)
                    if analog_keys[1] > .7:
                        data=data="DriveCommand_leftWheel1_rightWheel1_leftWheel2_rightWheel2_leftWheel3_rightWheel3_backward"
                        print(data)
                        client_socket.sendTo (data, address)
                    
            
            
