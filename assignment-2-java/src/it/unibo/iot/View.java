package it.unibo.iot;



import java.util.Optional;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.stage.Stage;
import jssc.SerialPortList;

/**
 * View class that initializes a graphic user interface and a communication interface to arduino serial
 */
public class View extends Application {
    private Stage primaryStage;
    private CommunicationInterface comm;
    private SceneController sceneController;
    private Controller controller;
    private static final int BAUD_RATE = 115200;
    private static final int WIDTH = 1500;
    private static final int HEIGHT = 1000;


    /**
     * {@inheritDoc}
     * 
     */
    @Override
    public void start(final Stage primaryStage) throws Exception {
        this.primaryStage = primaryStage;
        
        String[] portNames = SerialPortList.getPortNames();
        this.comm = new CommunicationInterfaceImpl(portNames[0], BAUD_RATE);
        
        this.controller = new Controller(this, new MessageAgent(), this.comm);    
        
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/mainGUI.fxml"));
        Parent root = (Parent) loader.load();
        this.sceneController = loader.getController();
  
        this.primaryStage.setTitle("Statistics Window");
        this.primaryStage.setScene(new Scene(root));
        this.primaryStage.setWidth(WIDTH);
        this.primaryStage.setHeight(HEIGHT);
        
        this.primaryStage.show();
    }
    
    /**
     * 
     * @param newState
     * 
     * Method that passes to the SceneController the new system state received from
     * communication interface
     */
    public void updateState(String newState) {
        this.sceneController.updateStatusLabel(newState);
    }
    
    /**
     * 
     * @param time
     * @param value
     * @param flag
     * @throws InterruptedException
     * 
     * Method that passes to the SceneController new values to be added to the charts.
     */
    public void addValueToChart(double time, double value, String flag) throws InterruptedException {
        if (flag.equals("position")) {
            this.sceneController.addPositionValue(time, value);
        }
        else if (flag.equals("speed")) {
            this.sceneController.addSpeedValue(time, value);
        }
        else if (flag.equals("acc")) {
            this.sceneController.addAccValue(time, value);
        }  
    }
    
    /**
     * This method shows an alert when the experiment terminates. When user will press
     * the OK button experiment will be reset while the charts will be reset only when a new experiment starts. 
     */
    public void windowAlert() {
        Platform.runLater(() -> {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Motion Simulator");
            alert.setHeaderText("Experiment Terminated");
            alert.setContentText("Press OK to start a new experiment");
            alert.initOwner(this.primaryStage);
            Optional<ButtonType> buttonPressed = alert.showAndWait();
            
            if (buttonPressed.isPresent() && buttonPressed.get() == ButtonType.OK) {
                    this.comm.sendMessage("reset");
                    this.resetCharts();
            }
        });
    }
    
    /**
     * Method that resets every chart
     */
    public void resetCharts() {
        this.sceneController.resetSeries();
    }
    
    /**
     * 
     * @param frequency
     * 
     * Method that sends the frequency of the current experiment to the SceneController
     */
    public void sendFrequency(double frequency) {
        this.sceneController.setFrequencyLabel(frequency);
    }
    

    public static void main(final String[] args) {
        launch(args);    
    }
}
