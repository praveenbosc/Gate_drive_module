import socket
import struct
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: script.py <arg1> <arg2>")
        sys.exit(1)

    try:
        arg1 = int(sys.argv[1])
        arg2 = int(sys.argv[2])
    except ValueError:
        print("Arguments must be integers")
        sys.exit(1)

    try:
        with socket.socket() as s:
            s.connect(("127.0.0.1", 3003))
            cmd = struct.pack("=BBIBBBB", 9, 2, 1000, 35, arg1, 36, arg2)
            s.send(cmd)
    except socket.error as e:
        print(f"Socket error: {e}")
        sys.exit(1)
    except struct.error as e:
        print(f"Struct packing error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
