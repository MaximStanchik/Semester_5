package by.stanchik.springbankapp.forms;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class EditCardForm {
    private String index;
    private String number;
    private String client;
}
