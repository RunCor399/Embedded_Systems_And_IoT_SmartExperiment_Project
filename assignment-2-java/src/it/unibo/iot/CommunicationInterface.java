package it.unibo.iot;

public interface CommunicationInterface {
    
    /**
     * @param message
     * 
     * Method that sends a message to arduino writing bytes into Serial
     */
    void sendMessage(String message);
    
    /**
     * 
     * @return Message from the queue
     * @throws InterruptedException
     * 
     * Method that extracts from the queue a message
     */
    String receiveMessage() throws InterruptedException;
    
    /**
     * Method that controls if message queue is empty
     * @return true if not empty, false otherwise
     */
    boolean messageAvailable();
}
