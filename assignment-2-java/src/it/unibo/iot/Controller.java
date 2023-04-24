package it.unibo.iot;

/**
 * 
 * Controller class used by MessageAgent thread to send messages to the View
 */
public class Controller {
    private final View view;
    private final MessageAgent agent;
    private final CommunicationInterface commInterface;
    public enum State {INITIALIZATION, EXPERIMENT_RUNNING, EXPERIMENT_FINISHED, POWERSAVE, ERROR};
    private double period;
    private int valueCounter;
    private String valueType;
    
    Controller(View view, MessageAgent agent, CommunicationInterface commInterface){
        this.view = view;
        this.agent = agent;
        this.commInterface = commInterface;
        this.valueCounter = 0;
        this.valueType = "init";
        this.agent.setParams(this, this.commInterface);
        this.agent.start();
    }
    
    /**
     * 
     * @param message
     * @throws InterruptedException
     * 
     * Method that parses a message received from MessageAgent in order to understand what kind of message it is
     */
    void parseMessage(String message) throws InterruptedException {
        
        if (State.EXPERIMENT_FINISHED.toString().equals(message)) {
            this.view.windowAlert();
        }
        
        for(State state : State.values()) {
            if(state.toString().equals(message)) {
                this.view.updateState(message);
                this.valueCounter = 0;
                this.valueType = "position";
                return;
            }
        }
        
            if (this.valueType.equals("init")) {
                return;
            }
            
            else if(this.valueType.equals("position")) {
                this.view.addValueToChart(this.period * this.valueCounter, Double.valueOf(message), this.valueType);
                this.valueType = "speed";
            }
            
            else if(this.valueType.equals("speed")) {
                this.view.addValueToChart(this.period * this.valueCounter, Double.valueOf(message), this.valueType);
                this.valueType = "acc";
            }
            else {
                this.view.addValueToChart(this.period * this.valueCounter, Double.valueOf(message), this.valueType);
                this.valueType = "position";
                this.valueCounter += 1;
            }
    }
    
    /**
     * 
     * @param period
     * 
     * Method that converts period unit of measure and computes frequency to be sent to the view
     */
    void setupPeriod(double period) {
        this.period = period/1000;
        double frequency = (double) (1000.0 / period);

        this.view.sendFrequency(((int)(frequency*100.0) / 100.0));
    }
}


