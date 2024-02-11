import rospy
from ultrasonic.msg import US
import serial.tools.list_ports

class ultrasonicNODE():
    def __init__(self):
        """The purpose of this node is to get the ultrasonic data from the esp32 with the configured parameters
        and post the data on a ROS topic.
        """
        
        rospy.init_node('ultrasonicNODE', anonymous=False)
        
        # Ultrasonic publisher object
        self.ultrasonic_publisher = rospy.Publisher("/automobile/ultrasonic", US, queue_size=1)
        
    #================================ RUN ================================================
    def run(self):
        """Apply the initializing methods and start the thread. 
        """
        rospy.loginfo("starting ultrasonicNODE")
        self._init_ultrasonic()
        
        while not rospy.is_shutdown():
            ultrasonic = US()
            ports = serial.tools.list_ports.comports()
            serialInst = serial.Serial()

            portsList = []

            for onePort in ports:
                portsList.append(str(onePort))
                print(str(onePort))

            val = input("Select Port: COM")

            for x in range(0,len(portsList)):
                if portsList[x].startswith("COM" + str(val)):
                    portVar = "COM" + str(val)
                    print(portVar)

            serialInst.baudrate = 115200
            serialInst.port = portVar
            serialInst.open()

            while True:
                if serialInst.in_waiting:
                    packet = serialInst.readline()
                    ultrasonic.front=packet.decode('utf').rstrip('\n')
                    packet = serialInst.readline()
                    ultrasonic.rear=packet.decode('utf').rstrip('\n')
                    packet = serialInst.readline()
                    ultrasonic.left=packet.decode('utf').rstrip('\n')
                    packet = serialInst.readline()
                    ultrasonic.right=packet.decode('utf').rstrip('\n')
                    self.ultrasonic_publisher.publish(ultrasonic)
                    print(ultrasonic)
            
    #================================ INIT ULTRASONIC ========================================
    def _init_ultrasonic(self):
        """Init the ultrasonic read port
        """ 
            
if __name__ == "__main__":
    usNod = ultrasonicNODE()
    usNod.run()