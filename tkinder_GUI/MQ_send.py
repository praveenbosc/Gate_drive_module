import posix_ipc
import json

# Define the message queue name
queue_name = "/example_queue"

# Create a new message queue or open an existing one
mq = posix_ipc.MessageQueue(queue_name, posix_ipc.O_CREAT)

# Define the structure to be sent
data = ["name" ,"Alice","age" ,"city","New York"]

# Convert the structure to a JSON string
message = json.dumps(data)

# Send the message to the message queue
mq.send(message)

# Close the message queue
mq.close()

print("Message sent successfully.")
