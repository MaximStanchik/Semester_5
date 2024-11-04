package by.stanchik.springbankapp.controller;

import by.stanchik.springbankapp.forms.CardForm;
import by.stanchik.springbankapp.forms.EditCardForm;
import by.stanchik.springbankapp.model.Card;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import java.util.ArrayList;
import java.util.List;

@Slf4j
@Controller
@RequestMapping
public class BankController {
    private static List<Card> cards = new ArrayList<Card>();

    static {
        cards.add(new Card("2398 8437 4321 3476", "Admin_0001"));
        cards.add(new Card("2134 4545 1222 3433", "Admin_0002"));
    }

    @Value("${welcome.message}")
    private String message;

    @Value("${error.message}")
    private String errorMessage;

    @GetMapping(value = {"/", "/index"})
    public ModelAndView index(Model model) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("index");
        model.addAttribute("message", message);
        log.info("/index was called");
        return modelAndView;
    }

    @GetMapping(value = {"/allcards"})
    public ModelAndView personList(Model model) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("cardlist");
        model.addAttribute("cards", cards);
        return modelAndView;
    }

    @GetMapping(value = {"/addcard"})
    public  ModelAndView showAddPersonPage(Model model) {
        ModelAndView modelAndView = new ModelAndView("addcard");
        CardForm cardForm = new CardForm();
        model.addAttribute("cardform", cardForm);

        return modelAndView;
    }

    @GetMapping(value = {"/editcardinfo"})
    public ModelAndView showEditCardInfo(Model model) {
        ModelAndView modelAndView = new ModelAndView("editcardinfo");
        EditCardForm editCardForm = new EditCardForm();
        model.addAttribute("editcardinfo", editCardForm);
            return modelAndView;
    }

    @PostMapping("/deletecard/{index}")
    public String deleteCard (@PathVariable int index, Model model) {
        if (index >= 0 && index < cards.size()) {
            cards.remove(index);
        }
        model.addAttribute("cards", cards);
        return "redirect:/allcards";
    }

    @PostMapping("/editcard/{index}")
    public String editCard(@PathVariable int index, Model model) {
        Card cardToEdit = cards.get(index);
        EditCardForm editCardForm = new EditCardForm(String.valueOf(index), cardToEdit.getNumber(), cardToEdit.getClient());
        model.addAttribute("editCardForm", editCardForm);
        return "editcardinfo";
    }

    @PostMapping("/updatecard")
    public String updateCard(@ModelAttribute(name = "editCardInfo") EditCardForm editCardForm) {
        int index = Integer.parseInt(editCardForm.getIndex());
        if (index >= 0 && index < cards.size()) {
            Card updatedCard = new Card(editCardForm.getNumber(), editCardForm.getClient());
            cards.set(index, updatedCard);
        }
        return "redirect:/allcards";
    }

    @PostMapping(value = {"/addcard"})
    public ModelAndView savePerson(Model model, @ModelAttribute("cardform") CardForm cardForm) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("cardlist");
        String number = cardForm.getNumber();
        String client = cardForm.getClient();

        if (number != null && client.length() > 0 //
                && client != null && client.length() > 0) {
            Card newCard = new Card(number, client);
            cards.add(newCard);
            model.addAttribute("cards",cards);
            return modelAndView;
        }

        model.addAttribute("errorMessage", errorMessage);
        modelAndView.setViewName("addcard");
        return modelAndView;
    }

}

