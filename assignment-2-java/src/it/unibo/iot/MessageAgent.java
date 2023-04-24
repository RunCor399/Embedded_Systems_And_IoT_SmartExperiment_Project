package it.unibo.iot;


/**
 * Class that runs a thread which constantly checks for new messages from arduino.
 * Once a message is received it will be sent to the Controller
 */
public class MessageAgent extends Thread {
    
    private Controller controller;
    private CommunicationInterface commInterface;
    private boolean stop;
    private boolean setup;
    
    public MessageAgent() {
        this.stop = false;
        this.setup = false;
    }
    
    public void setParams(Controller controller, CommunicationInterface commInterface) {
        this.controller = controller;
        this.commInterface = commInterface;
    }
    
    
    public void run() {
        while (!this.isStopped()) { 

            if (this.commInterface.messageAvailable()) {
                try {
                    String message = this.commInterface.receiveMessage();
                    
                    if (this.setup) {
                        this.receivePeriodValue(message);
                        
                    }
                    else if (!this.setup && !message.equals("setup")) {
                        this.sendMessageToController(message);  
                    }
                    else {
                        this.setupSystem(message); 
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
    /**
     * 
     * @param message
     * @throws InterruptedException
     * 
     * Method that sends a message to the Controller
     */
    public void sendMessageToController(String message) throws InterruptedException {
        this.controller.parseMessage(message);
    }
    
    /**
     * 
     * @param message
     * 
     * Method that enables setup mode, next message received from arduino will be the period
     */
    public void setupSystem(String message) {
        if (message.equals("setup")) {
            this.setup = !this.setup;
        }
    }
    
    /**
     * 
     * @param message
     * 
     * Method that sends to the Controller the experiment period chosen by the user
     */
    public void receivePeriodValue(String message) {
        this.setup = !this.setup;
        this.controller.setupPeriod(Integer.valueOf(message));
    }
    
    public boolean isStopped() {
        return this.stop;
    }
    
    
}
