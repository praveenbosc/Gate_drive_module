# For creating Tab / container / window

# import tkinter
# m = tkinter.Tk()
# m.mainloop()
#########################
# For creating Tab / container Dedicated Labling 

# import tkinter as tk

# app = tk.Tk()
# app.title("DAQ GUI")
# app.geometry("1280x1080")
# app.mainloop()

#########################
# from tkinter import *
# root = Tk()

# input = Entry(root,width=50)
# input.pack()

# def onclick():
#     label = Label(root, text='Welcome')
#     label1 = Label(root, text=input.get())
#     # label.grid(row=0, column=1)
#     label.pack()
#     label1.pack()

# button = Button(root,text="Don't touch!!!",bg="blue",fg="red",command=onclick,state=ACTIVE)
# # button.grid(row=0, column=0)
# button.pack()

# # root.geometry("1280x1080")
# root.mainloop()

#############################
# from tkinter import *
# from tkinter import messagebox   
  
# top = Tk()  
  
# top.geometry("200x100")  
  
# def fun():  didicated
#     messagebox.showinfo("Hello", "Red Button clicked")  
#     # label = Label(top, text='Welcome')
#     # label.pack()
  
  
# b1 = Button(top,text = "Red",command = fun,activeforeground = "red",activebackground = "pink",pady=10)  
  
# b2 = Button(top, text = "Blue",activeforeground = "blue",activebackground = "pink",pady=10)  
  
# b3 = Button(top, text = "Green",activeforeground = "green",activebackground = "pink",pady = 10)  
  
# b4 = Button(top, text = "Yellow",activeforeground = "yellow",activebackground = "pink",pady = 10)  
  
# b1.pack(side = LEFT)  
  
# b2.pack(side = RIGHT)  
  
# b3.pack(side = TOP)  
  
# b4.pack(side = BOTTOM)  
  
# top.mainloop()  

# from tkinter import *  
  
# top = Tk()  
  
# top.geometry("400x250")  
  
# name = Label(top, text = "Name").place(x = 30,y = 50)  
  
# email = Label(top, text = "Email").place(x = 30, y = 90)  
  
# password = Label(top, text = "Password" ).place(x = 30, y = 130)  
  
# sbmitbtn = Button(top, text = "Submit",activebackground = "pink", activeforeground = "blue").place(x = 30, y = 170)  
  
# e1 = Entry(top).place(x = 80, y = 50)  
  
  
# e2 = Entry(top).place(x = 80, y = 90)  
  
  
# e3 = Entry(top,show="*").place(x = 95, y = 130)  
  
# top.mainloop()  


# app = tk.Tk()
# app.title("DAQ GUI")
# app.mainloop()
##########################
# For creating Tab / container Dedicated Labling and size of the window

# import tkinter as tk
# app = tk.Tk()
# app.title("DAQ GUI")
# app.geometry("1280x1080")
# app.mainloop()

##################################
# from tkinter import *
# root = Tk()

# input = Entry(root,width=50)
# input.pack()

# def onclick():
#     label = Label(root, text='Welcome')
#     label1 = Label(root, text=input.get())
#     # label.grid(row=0, column=1)
#     label.pack()
#     label1.pack()

# button = Button(root,text="Don't touch!!!",bg="blue",fg="red",command=onclick,state=ACTIVE)
# # button.grid(row=0, column=0)
# button.pack()

# # root.geometry("1280x1080")
# root.mainloop()

######################################
# from tkinter import *
# from tkinter import messagebox   
  
# top = Tk()  
  
# top.geometry("200x100")  
  
# def fun():  
#     messagebox.showinfo("Hello", "Red Button clicked")  
#     # label = Label(top, text='Welcome')
#     # label.pack()
  
  
# b1 = Button(top,text = "Red",command = fun,activeforeground = "red",activebackground = "pink",pady=10)  
  
# b2 = Button(top, text = "Blue",activeforeground = "blue",activebackground = "pink",pady=10)  
  
# b3 = Button(top, text = "Green",activeforeground = "green",activebackground = "pink",pady = 10)  
  
# b4 = Button(top, text = "Yellow",activeforeground = "yellow",activebackground = "pink",pady = 10)  
  
# b1.pack(side = LEFT)  
  
# b2.pack(side = RIGHT)  
  
# b3.pack(side = TOP)  
  
# b4.pack(side = BOTTOM)  
  
# top.mainloop()  

############################################
# from tkinter import *  
  
# top = Tk()  
  
# top.geometry("400x250")  
  
# name = Label(top, text = "Name").place(x = 30,y = 50)  
  
# email = Label(top, text = "Email").place(x = 30, y = 90)  
  
# password = Label(top, text = "Password" ).place(x = 30, y = 130)  
  
# sbmitbtn = Button(top, text = "Submit",activebackground = "pink", activeforeground = "blue").place(x = 30, y = 170)  
  
# e1 = Entry(top).place(x = 80, y = 50)  
  
  
# e2 = Entry(top).place(x = 80, y = 90)  
  
  
# e3 = Entry(top,show="*").place(x = 95, y = 130)  
  
# top.mainloop()  

###############################################

# import tkinter as tk

# root = tk.Tk()
# root.title('Tkinter Window - Center')

# window_width = 300
# window_height = 200

# # get the screen dimension
# screen_width = root.winfo_screenwidth()
# screen_height = root.winfo_screenheight()

# # find the center point
# center_x = int(screen_width/2 - window_width / 2)
# center_y = int(screen_height/2 - window_height / 2)

# # set the position of the window to the center of the screen
# root.geometry(f'{window_width}x{window_height}+{center_x}+{center_y}')

# root.mainloop()

#############################
# import tkinter as tk
# from tkinter import ttk
# from tkinter.messagebox import showinfo

# root = tk.Tk()
# root.geometry('300x200')
# root.resizable(False, False)
# root.title('Checkbox Demo')

# agreement = tk.StringVar(value=2)


# def agreement_changed():
#     tk.messagebox.showinfo(title='Result',
#                         message=agreement.get())


# ttk.Checkbutton(root,
#                 text='I agree',
#                 command=agreement_changed,
#                 variable=agreement,
#                 onvalue='agree',
#                 offvalue='disagree').pack()


# root.mainloop()

# import tkinter as tk
# from tkinter import ttk
# import socket
# import threading

# # Initialize Tkinter root
# root = tk.Tk()
# root.title("TCP Client")

# # Create a notebook (tabbed interface)
# notebook = ttk.Notebook(root)
# notebook.pack(expand=True, fill='both')

# # Create frames for each tab
# input_frame = ttk.Frame(notebook)
# receive_frame = ttk.Frame(notebook)

# # Add frames to notebook
# notebook.add(input_frame, text="Input")
# notebook.add(receive_frame, text="Receive")

# # Input Frame Widgets
# labels = ["IP Address", "Port", "Input 1", "Input 2", "Input 3"]
# entries = []

# for i, label in enumerate(labels):
#     tk.Label(input_frame, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(input_frame)
#     entry.grid(row=i, column=1, padx=5, pady=5)
#     entries.append(entry)

# def connect():
#     ip = entries[0].get()
#     port = int(entries[1].get())
#     inputs = [entry.get() for entry in entries[2:]]
#     print(f"Connecting to {ip}:{port} with inputs {inputs}")

#     # TCP connection
#     try:
#         global client_socket
#         client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         client_socket.connect((ip, port))
#         for input_data in inputs:
#             client_socket.sendall(input_data.encode('utf-8'))
#         print("Data sent to server.")
#     except Exception as e:
#         print(f"Error connecting to server: {e}")

# tk.Button(input_frame, text="Connect", command=connect).grid(row=len(labels), column=0, columnspan=2, pady=10)

# # Receive Frame Widgets
# receive_text = tk.Text(receive_frame, height=10, width=50)
# receive_text.pack(pady=10)

# def receive_data():
#     while True:
#         try:
#             data = client_socket.recv(14)  # Receive 14 bytes
#             if data:
#                 receive_text.insert(tk.END, f"Received: {data}\n")
#                 receive_text.see(tk.END)
#         except:
#             break

# def start_receiving():
#     receive_thread = threading.Thread(target=receive_data)
#     receive_thread.daemon = True
#     receive_thread.start()

# tk.Button(receive_frame, text="Start Receiving", command=start_receiving).pack(pady=10)

# # Run the Tkinter event loop
# root.mainloop()

#######################
# import tkinter as tk
# from tkinter import ttk
# from tkinter.messagebox import showinfo

# # root window
# root = tk.Tk()
# root.geometry("300x150")
# root.resizable(False, False)
# root.title('Sign In')

# # store email address and password
# email = tk.StringVar()
# password = tk.StringVar()


# def login_clicked():
#     """ callback when the login button clicked
#     """
#     msg = f'You entered email: {email.get()} and password: {password.get()}'
#     showinfo(
#         title='Information',
#         message=msg
#     )


# # Sign in frame
# signin = ttk.Frame(root)
# signin.pack(padx=10, pady=10, fill='x', expand=True)


# # email
# email_label = ttk.Label(signin, text="Email Address:")
# email_label.pack(fill='x', expand=True)

# email_entry = ttk.Entry(signin, textvariable=email)
# email_entry.pack(fill='x', expand=True)
# email_entry.focus()

# # password
# password_label = ttk.Label(signin, text="Password:")
# password_label.pack(fill='x', expand=True)

# password_entry = ttk.Entry(signin, textvariable=password, show="*")
# password_entry.pack(fill='x', expand=True)

# # login button
# login_button = ttk.Button(signin, text="Login", command=login_clicked)
# login_button.pack(fill='x', expand=True, pady=10)


# root.mainloop()

########################

# import tkinter as tk

# def show_entry_content():
#     print(entry.get())

# # Create the main window
# root = tk.Tk()
# root.title("Tkinter Entry Example")

# # Create an Entry widget
# entry = tk.Entry(root)
# entry.pack(pady=10)

# # Create a Button to trigger an action
# button = tk.Button(root, text="Show Entry Content", command=show_entry_content)
# button.pack(pady=10)

# # Run the application
# root.mainloop()

######################

# import tkinter as tk

# def get_entry_text():
#     input_text = entry_var.get()
#     print(f"Entered text: {input_text}")

# root = tk.Tk()
# root.title("Tkinter Entry Example")
# root.geometry("300x200")

# entry_var = tk.StringVar()
# entry = tk.Entry(root, textvariable=entry_var, width=30)
# entry.pack(pady=20)

# entry.focus()

# button = tk.Button(root, text="Get Entry Text", command=get_entry_text)
# button.pack(pady=10)

# root.mainloop()
############################

# import tkinter as tk
# from tkinter import Button, Entry, Label, ttk

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

# input_labels = ["Start_of_frame", "Packet_identifier", "Data_1", "Data_2", "Checksum"]
# input_entries = []

# def entry_content():
#     for entry in input_entries:
#         print(entry.get())

# # Create input labels and entries
# for i, label in enumerate(input_labels):
#     tk.Label(frame1, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame1, justify='left', highlightbackground='blue', selectforeground='green')
#     entry.grid(row=i, column=1, padx=5, pady=5)
#     input_entries.append(entry)

# # Create button to get input data
# button_0 = Button(frame1, text='Input_data', activebackground='pink', activeforeground='blue', command=entry_content)
# button_0.grid(row=len(input_labels), column=1, padx=5, pady=5)

# output_labels = ["Start_of_frame", "Data_1", "Data_2", "Data_3", "Data_4", "Data_5", "Data_6", "Data_7", 
#                  "Data_8", "Data_9", "Data_10", "Data_11", "Data_12", "Data_13", "Data_14", "Checksum"]

# # Create output labels and entries
# for i, label in enumerate(output_labels):
#     tk.Label(frame2, text=label).grid(row=i, column=0, padx=5, pady=5)
#     entry = tk.Entry(frame2)
#     entry.grid(row=i, column=1, padx=5, pady=5)

# # Create button to simulate receiving data
# button_1 = Button(frame2, text='receive_data', activebackground='pink', activeforeground='red')
# button_1.grid(row=len(output_labels), column=1, padx=5, pady=5)

# root.mainloop()

import tkinter as tk

# Create the main window
root = tk.Tk()
root.title("Store Data in List")

# Create an empty list to store data
data_list = []

# Function to get data from entry and store in the list
def store_data():
    data = entry.get()
    if data:  # Check if there is any input
        data_list.append(data)
        entry.delete(0, tk.END)  # Clear the entry widget
        print(data_list)  # Print the list to console

# Create an Entry widget
entry = tk.Entry(root, width=50)
entry.pack(pady=10)

# Create a Button widget
button = tk.Button(root, text="Store Data", command=store_data)
button.pack(pady=10)

# Run the application
root.mainloop()
