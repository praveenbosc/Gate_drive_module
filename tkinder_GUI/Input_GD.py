# import tkinter as tk
# from tkinter import Button, Entry, Label, ttk
# import socket
# import pickle

# # root window
# root = tk.Tk()
# root.geometry("640x1080")
# root.title('Gate_Driver_Module')

# # create a notebook
# notebook = ttk.Notebook(root)
# notebook.pack(expand=True)

# # create frames
# frame1 = ttk.Frame(notebook)
# frame2 = ttk.Frame(notebook)

# frame1.pack(fill='both', expand=True)
# frame2.pack(fill='both', expand=True)

# # add frames to notebook
# notebook.add(frame1, text='Input')
# notebook.add(frame2, text='Receive')

# button_1 = Button(frame2, text='receive_data', activebackground='pink',activeforeground='red')
# # button_0 = Button(frame1, text='Input_data', activebackground ='pink', activeforeground='blue')

# def send_list(data_list, host='127.0.0.1', port=3003):
#     # Create a TCP/IP socket
#     with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#         # Connect to the server
#         s.connect((host, port))
#         # Serialize the list using pickle
#         data = pickle.dumps(data_list)
#         # Send data to the server
#         s.sendall(data)
#         print(f"Sent: {data_list}")

# input_lables = ["Packet_identityfier","Data" ]
# input_entries =[]
# data_list = []

# entry =0

# def entry_content():
#     for i in input_entries:
#         # print(i.get())
#         data=i.get()
#         if data:  # Check if there is any input
#             data_list.append(data)
#             entry.delete(0, tk.END)  # Clear the entry widget
#     send_list(data_list)
    
# for i, lable in enumerate(input_lables):
#             tk.Label(frame1, text=lable).grid(row =i,column=0,padx=5,pady=5)
#             entry = tk.Entry(frame1,justify='left',highlightbackground='blue',selectforeground='green')
#             entry.grid(row=i,column=1,padx=5,pady=5)
#             input_entries.append(entry)
            
# button_0 = Button(frame1, text='Input_data', activebackground ='pink', activeforeground='blue', command = entry_content)
# button_0.grid()

# output_lables = ["Start_of_frame","Data_1","Data_2","Data_3","Data_4","Data_5","Data_6","Data_7","Data_8","Data_9","Data_10","Data_11","Data_12","Data_13","Data_14","Checksum" ]

# for i, lable in enumerate(output_lables):
#     tk.Label(frame2, text=lable).grid(row =i,column=0,padx=5,pady=5)
#     entry = tk.Entry(frame2)
#     entry.grid(row=i,column=1,padx=5,pady=5)

# # button_1.pack(side='top')

# root.mainloop()





# import posix_ipc
# import json


 # Define the message queue name
# queue_name = "/mq_seq_to_motor_controller"


    # # Create a new message queue or open an existing one
    # mq = posix_ipc.MessageQueue(queue_name, posix_ipc.O_CREAT)

    #     # Convert the structure to a JSON string
    # message = json.dumps(data_list)

    # # Send the message to the message queue
    # mq.send(message)
    
# import tkinter as tk
# from tkinter import Button, Entry, Label, ttk
# import socket
# import pickle
# import time
# import struct
# import threading
# import sys

# # root window
# root = tk.Tk()
# root.geometry("640x480")
# root.title('Gate_Driver_Module')

# # create a notebook
# notebook = ttk.Notebook(root)
# notebook.pack(expand=True)

# # create frames
# frame1 = ttk.Frame(notebook)
# frame2 = ttk.Frame(notebook)

# frame1.pack(fill='both', expand=True)
# frame2.pack(fill='both', expand=True)

# # add frames to notebook
# notebook.add(frame1, text='Input')
# notebook.add(frame2, text='Receive')

# button_1 = Button(frame2, text='Receive Data', activebackground='pink', activeforeground='red')

# # Create a global variable to store the socket
# client_socket = None

# def send_list(data_list, host='127.0.0.1', port=3003):
#     s=socket.socket()
#     s.connect(("127.0.0.1", 3003))

#     cmd = struct.pack("=BBIBBBB", 9, 2, 1000, 35, data_list[0], 36, data_list[1])
#     s.send(cmd)
    
#     print(f"Sent: {data_list}")

# def disconnect():
#     global client_socket
#     if client_socket:
#         client_socket.close()
#         client_socket = None
#         print("Disconnected from the server")

# input_labels = ["Packet_identifier", "Data"]
# input_entries = []
# data_list = []

# def entry_content():
#     global data_list
#     data_list = []  # Clear the list before adding new data
#     for i in input_entries:
#         data = i.get()
#         if data:  # Check if there is any input
#             data_list.append(data)
#             i.delete(0, tk.END)  # Clear the entry widget
#     send_list(data_list)

# for i, label in enumerate(input_labels):
#     tk.Label(frame1, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame1, justify='left', highlightbackground='blue', selectforeground='green')
#     entry.grid(row=i, column=1, padx=5, pady=5)
#     input_entries.append(entry)

# button_0 = Button(frame1, text='Input Data', activebackground='pink', activeforeground='blue', command=entry_content)
# button_0.grid()

# disconnect_button = Button(frame1, text='Disconnect', activebackground='pink', activeforeground='red', command=disconnect)
# disconnect_button.grid()

# output_labels = ["Start_of_frame", "Data_1", "Data_2", "Data_3", "Data_4", "Data_5", "Data_6", "Data_7", "Data_8", "Data_9", "Data_10", "Data_11", "Data_12", "Data_13", "Checksum"]

# for i, label in enumerate(output_labels):
#     tk.Label(frame2, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame2)
#     entry.grid(row=i, column=1, padx=5, pady=5)

# root.mainloop()
#######################################################
import tkinter as tk
from tkinter import Button, Entry, Label, ttk
import socket
import struct

# root window
root = tk.Tk()
root.geometry("640x480")
root.title('Gate_Driver_Module')

# create a notebook
notebook = ttk.Notebook(root)
notebook.pack(expand=True)

# create frames
frame1 = ttk.Frame(notebook)
frame2 = ttk.Frame(notebook)

frame1.pack(fill='both', expand=True)
frame2.pack(fill='both', expand=True)

# add frames to notebook
notebook.add(frame1, text='Input')
notebook.add(frame2, text='Receive')

button_1 = Button(frame2, text='Receive Data', activebackground='pink', activeforeground='red')

# Create a global variable to store the socket
client_socket = None

def connect_to_server(host='127.0.0.1', port=3003):
    global client_socket
    client_socket = socket.socket()
    client_socket.connect((host, port))
    print("Connected to the server")

def send_list(data_list):
    global client_socket
    if client_socket:
        cmd = struct.pack("=BBIBBBB", 9, 2, 1000, 35, int(data_list[0]), 36, int(data_list[1]))
        client_socket.send(cmd)
        print(f"Sent: {int(data_list[0]),int(data_list[1])}")
    else:
        print("Not connected to the server")

def disconnect():
    global client_socket
    if client_socket:
        client_socket.close()
        client_socket = None
        print("Disconnected from the server")

input_labels = ["Packet_identifier", "Data"]
input_entries = []
data_list = []

def entry_content():
    global data_list
    data_list = []  # Clear the list before adding new data
    for i in input_entries:
        data = i.get()
        if data:  # Check if there is any input
            data_list.append(data)
            i.delete(0, tk.END)  # Clear the entry widget
    send_list(data_list)

for i, label in enumerate(input_labels):
    tk.Label(frame1, text=label).grid(row=i, column=0, padx=5, pady=5)
    entry = tk.Entry(frame1, justify='left', highlightbackground='blue', selectforeground='green')
    entry.grid(row=i, column=1, padx=5, pady=5)
    input_entries.append(entry)

connect_button = Button(frame1, text='Connect', activebackground='pink', activeforeground='blue', command=connect_to_server)
connect_button.grid()

send_button = Button(frame1, text='Send Data', activebackground='pink', activeforeground='blue', command=entry_content)
send_button.grid()

disconnect_button = Button(frame1, text='Disconnect', activebackground='pink', activeforeground='red', command=disconnect)
disconnect_button.grid()

output_labels = ["Start_of_frame", "Data_1", "Data_2", "Data_3", "Data_4", "Data_5", "Data_6", "Data_7", "Data_8", "Data_9", "Data_10", "Data_11", "Data_12", "Data_13", "Checksum"]

for i, label in enumerate(output_labels):
    tk.Label(frame2, text=label).grid(row=i, column=0, padx=5, pady=5)
    entry = tk.Entry(frame2)
    entry.grid(row=i, column=1, padx=5, pady=5)

root.mainloop()
###########################################################

# import tkinter as tk
# from tkinter import Button, Entry, Label, ttk
# import socket
# import struct
# import threading

# # root window
# root = tk.Tk()
# root.geometry("640x480")
# root.title('Gate_Driver_Module')

# # create a notebook
# notebook = ttk.Notebook(root)
# notebook.pack(expand=True)

# # create frames
# frame1 = ttk.Frame(notebook)
# frame2 = ttk.Frame(notebook)

# frame1.pack(fill='both', expand=True)
# frame2.pack(fill='both', expand=True)

# # add frames to notebook
# notebook.add(frame1, text='Input')
# notebook.add(frame2, text='Receive')

# input_labels = ["Seq id", "Seq cmd"]
# input_entries = []

# def entry_content():
#     # Send data via socket
#     threading.Thread(target=send_data).start()

# # Create input labels and entries
# for i, label in enumerate(input_labels):
#     tk.Label(frame1, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame1, justify='left', highlightbackground='blue', selectforeground='green')
#     entry.grid(row=i, column=1, padx=5, pady=5)
#     input_entries.append(entry)

# # Create button to get input data
# button_0 = Button(frame1, text='Input_data', activebackground='pink', activeforeground='blue', command=entry_content)
# button_0.grid(row=len(input_labels), column=1, padx=5, pady=5)

# output_labels = ["Data_1", "Data_2"]
# output_entries = []

# # Create output labels and entries
# for i, label in enumerate(output_labels):
#     tk.Label(frame2, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame2)
#     entry.grid(row=i, column=1, padx=5, pady=5)
#     output_entries.append(entry)

# # Create button to simulate receiving data
# button_1 = Button(frame2, text='receive_data', activebackground='pink', activeforeground='red', command=lambda: threading.Thread(target=receive_data).start())
# button_1.grid(row=len(output_labels), column=1, padx=5, pady=5)

# def send_data():
#     try:
#         s = socket.socket()
#         s.connect(("1.1.1.2", 3003))

#         # Get input data
#         data = [entry.get() for entry in input_entries]
#         if len(data) < 2:
#             print("Not enough data provided.")
#             return

#         # Convert data to appropriate format
#         cmd = struct.pack("=BB", int(data[0]), int(data[1]))
#         s.send(cmd)
#         s.close()
#     except Exception as e:
#         print(f"Error sending data: {e}")

# def receive_data():
#     try:
#         s = socket.socket()
#         s.connect(("127.0.0.1", 3003))

#         # Receive data
#         response = s.recv(1024)
#         unpacked_data = struct.unpack("=II", response)  # Adjust the format to match the data you expect

#         # Update output entries
#         for i, entry in enumerate(output_entries):
#             entry.delete(0, tk.END)
#             entry.insert(0, str(unpacked_data[i]))

#         s.close()
#     except Exception as e:
#         print(f"Error receiving data: {e}")

# # Start the GUI main loop
# root.mainloop()
