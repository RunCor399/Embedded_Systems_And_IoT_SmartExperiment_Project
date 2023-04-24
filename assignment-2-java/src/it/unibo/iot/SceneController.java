package it.unibo.iot;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.chart.Axis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;

/**
 * SceneController class handles all the updates onto view elements
 */
public class SceneController {
    private ObservableList<XYChart.Series> positionSeries = FXCollections.observableArrayList();
    private ObservableList<XYChart.Data> positionData = FXCollections.observableArrayList();
    private ObservableList<XYChart.Series> speedSeries = FXCollections.observableArrayList();
    private ObservableList<XYChart.Data> speedData = FXCollections.observableArrayList();
    private ObservableList<XYChart.Series> accelerationSeries = FXCollections.observableArrayList();
    private ObservableList<XYChart.Data> accelerationData = FXCollections.observableArrayList();

    @FXML
    private VBox positionChartContainer;
    
    @FXML
    private VBox speedChartContainer;
    
    @FXML
    private VBox accelerationChartContainer;
    
    @FXML
    private Label statusLabel;
    
    @FXML
    private Label frequencyLabel;
    
    @FXML
    private Label positionLabel;
    
    @FXML
    private Label velocityLabel;
    
    @FXML
    private Label accelerationLabel;
    
    /**
     * Initialization method that creates each chart and adds each one onto the gui
     */
    @FXML
    public final void initialize() {
        this.positionSeries.add(new XYChart.Series("Position", this.positionData));
        this.speedSeries.add(new XYChart.Series("Speed", this.speedData));
        this.accelerationSeries.add(new XYChart.Series("Acceleration", this.accelerationData));
        
        Axis xPositionAxis = new NumberAxis("x", 0, 20, 1);
        Axis yPositionAxis = new NumberAxis("y", 0, 2, 0.1);
        
        Axis xSpeedAxis = new NumberAxis("x", 0, 20, 0.1);
        Axis ySpeedAxis = new NumberAxis("y", 0, 1.5, 0.05);
        
        Axis xAccAxis = new NumberAxis("x", 0 , 20, 0.1);
        Axis yAccAxis = new NumberAxis("y", 0, 2, 0.1);
        
        xPositionAxis.setLabel("Time (s)");
        yPositionAxis.setLabel("Position (m)");
        
        xSpeedAxis.setLabel("Time (s)");
        ySpeedAxis.setLabel("Speed (m/s)");
        
        xAccAxis.setLabel("Time (s)");
        yAccAxis.setLabel("Acceleration (m/s^2)");
        
        LineChart positionChart = new LineChart(xPositionAxis, yPositionAxis, this.positionSeries);
        LineChart speedChart = new LineChart(xSpeedAxis, ySpeedAxis, this.speedSeries);
        LineChart accelerationChart = new LineChart(xAccAxis, yAccAxis, this.accelerationSeries);
        
        positionChart.setCreateSymbols(false);
        speedChart.setCreateSymbols(false);
        accelerationChart.setCreateSymbols(false);
        
        this.positionChartContainer.getChildren().add(positionChart);
        this.speedChartContainer.getChildren().add(speedChart);
        this.accelerationChartContainer.getChildren().add(accelerationChart);
    }
    
    /**
     * 
     * @param newState
     * 
     * Methods that updates the state label with the current state
     */
    public void updateStatusLabel(String newState) {
        Platform.runLater(() -> {
            switch (newState) {
            case "INITIALIZATION":
                this.statusLabel.setStyle("-fx-font-weight: bold; -fx-text-fill: black");
                this.statusLabel.setText("Initialization");
                break;
                
            case "EXPERIMENT_RUNNING":
                this.statusLabel.setStyle("-fx-font-weight: bold; -fx-text-fill: green");
                this.statusLabel.setText("Experiment Running");
                break;
                
            case "EXPERIMENT_FINISHED":
                this.statusLabel.setStyle("-fx-font-weight: bold; -fx-text-fill: black");
                this.statusLabel.setText("Experiment Finished");
                break;
                
            case "ERROR":
                this.statusLabel.setStyle("-fx-font-weight: bold; -fx-text-fill: red");
                this.statusLabel.setText("Object Detection Error");
                break;
                
            case "POWERSAVE":
                this.statusLabel.setStyle("-fx-font-weight: bold; -fx-text-fill: black");
                this.statusLabel.setText("Powersave Mode");
                break;
            }
            
        }); 
    }
    
    /**
     * 
     * @param x
     * @param y
     * @throws InterruptedException
     * 
     * Method that adds a new point in the position chart
     */
    public void addPositionValue(double x, double y) throws InterruptedException {
        Platform.runLater(() -> {
            this.positionSeries.get(0).getData().add(new XYChart.Data(x, y));
            this.positionLabel.setText(String.valueOf(y) + "m");
        });
    }
    
    /**
     * 
     * @param x
     * @param y
     * @throws InterruptedException
     * 
     * Method that adds a new point in the velocity chart
     */
    public void addSpeedValue(double x, double y) throws InterruptedException {
        Platform.runLater(() -> {
            this.speedSeries.get(0).getData().add(new XYChart.Data(x, y));
            this.velocityLabel.setText(String.valueOf(y) + "m/s");
        });
        
    }
    
    /**
     * 
     * @param x
     * @param y
     * @throws InterruptedException
     * 
     * Method that adds a new point in the acceleration chart
     */
    public void addAccValue(double x, double y) throws InterruptedException {
        Platform.runLater(() -> {
            this.accelerationSeries.get(0).getData().add(new XYChart.Data(x, y));
            this.accelerationLabel.setText(String.valueOf(y) + "m/s^2");
        });
        
    }
    
    /**
     * Method that clears each Series stored data
     */
    public void resetSeries() {
            this.positionSeries.get(0).getData().clear();
            this.speedSeries.get(0).getData().clear();
            this.accelerationSeries.get(0).getData().clear();
    }
    
    /**
     * 
     * @param frequency
     * 
     * Method that updates frequency label
     */
    public void setFrequencyLabel(double frequency) {
        Platform.runLater(() -> {
            this.frequencyLabel.setText(String.valueOf(frequency) + "Hz");
        });  
    }

}
