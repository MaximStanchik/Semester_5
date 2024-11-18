package org.Stanchik.pages;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class AmazonSignIn {
    private WebDriver driver;
    private WebDriverWait webDriverWait;

    public AmazonSignIn (WebDriver webDriver) {
        this.driver = webDriver;
        this.webDriverWait = new WebDriverWait(webDriver, Duration.ofSeconds(10));
    }

    private By emailField = By.id("ap_email");
    private By continueButton = By.id("continue");
    private By passwordField = By.id("ap_password");
    private By signInButton = By.id("signInSubmit");

    public void OpenPage() {
        driver.get("https://www.amazon.com/ap/signin?openid.pape.max_auth_age=0&openid.return_to=https%3A%2F%2Fwww.amazon.com%2F%3Fref_%3Dnav_signin&openid.identity=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.assoc_handle=usflex&openid.mode=checkid_setup&openid.claimed_id=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.ns=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0");
    }

    public void AmazonAuthorization (String emailExample, String passwordExample) {
        WebElement email = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(emailField));
        email.sendKeys(emailExample);

        WebElement continueBut = driver.findElement(continueButton);
        continueBut.click();

        WebElement password = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(passwordField));
        password.sendKeys(passwordExample);

        WebElement signInBut = driver.findElement(signInButton);
        signInBut.click();
    }
}
