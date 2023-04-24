package it.unibo.iot;

import java.util.concurrent.*;
import jssc.*;

/**
 * 
 * @author manuel
 * 
 * Simple communication interface that stores and makes available messages received from serial into a thread-safe queue
 * 
 */
public class CommunicationInterfaceImpl implements CommunicationInterface, SerialPortEventListener {
    private SerialPort serialPort;
    private BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer("");
    
    
    public CommunicationInterfaceImpl(String port, int baudRate) throws SerialPortException {
        this.queue = new ArrayBlockingQueue<String>(100);
        
        this.serialPort = new SerialPort(port);
        
        this.setupSerialPort(baudRate);
        
    }
    
    @Override
    public void sendMessage(String message) {
        char[] array = (message+"\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++){
                bytes[i] = (byte) array[i];
        }
        try {
                synchronized (this.serialPort) {
                        this.serialPort.writeBytes(bytes);
                }
        } catch(Exception ex){
                ex.printStackTrace();
        }
    }

    @Override
    public String receiveMessage() throws InterruptedException {
        return this.queue.take();
    }

    @Override
    public boolean messageAvailable() {
        return !this.queue.isEmpty();
    }
    
    public void setupSerialPort(int baudRate) throws SerialPortException {
        this.serialPort.openPort();
        this.serialPort.setParams(baudRate, SerialPort.DATABITS_8,
                                            SerialPort.STOPBITS_1,
                                            SerialPort.PARITY_NONE);
        
        this.serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
                                           SerialPort.FLOWCONTROL_RTSCTS_OUT);
        
        this.serialPort.addEventListener(this);
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
                msg = msg.replaceAll("\r", "");
                        
                this.currentMsg.append(msg);
                        
                boolean goAhead = true;
                    while(goAhead) {
                        String msg2 = currentMsg.toString();
                        int index = msg2.indexOf("\n");
                        if (index >= 0) {
                            queue.put(msg2.substring(0, index));
                            currentMsg = new StringBuffer("");
                            if (index + 1 < msg2.length()) {
                                currentMsg.append(msg2.substring(index + 1)); 
                                }
                             } 
                        else {
                            goAhead = false;
                              }
                       }
                                
            } catch (Exception ex) {
                ex.printStackTrace();
                System.out.println("Errore ricezione messaggio: " + ex);
            }
        }
    }
}
