package org.Stanchik.pages;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class DemoqaCheckbox {
    private WebDriver driver;
    private WebDriverWait webDriverWait;

    public DemoqaCheckbox (WebDriver webDriver) {
        this.driver = webDriver;
        this.webDriverWait = new WebDriverWait(webDriver, Duration.ofSeconds(10));
    }

    private By homeCheckBoxLabel = By.cssSelector("label[for='tree-node-home']");
    private By homeCheckBoxInput = By.id("tree-node-home");

    public void openPage() {
        driver.get("https://demoqa.com/checkbox");
    }

    public void selectHomeCheckBox() {
        WebElement checkBoxLabel = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(homeCheckBoxLabel));
        WebElement checkBoxInput = driver.findElement(homeCheckBoxInput);

        if (!checkBoxInput.isSelected()) {
            checkBoxLabel.click();
        }

        System.out.println("Checkbox теперь выбран");
    }
}
