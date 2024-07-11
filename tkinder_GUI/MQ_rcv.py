import posix_ipc
import json

# Define the message queue name
queue_name = "/example_queue"

# Open the existing message queue
mq = posix_ipc.MessageQueue(queue_name)

# Receive the message from the message queue
message, _ = mq.receive()

# Convert the JSON string back to a dictionary
data = json.loads(message.decode())

# Close the message queue
mq.close()

print("Received message:", data)
