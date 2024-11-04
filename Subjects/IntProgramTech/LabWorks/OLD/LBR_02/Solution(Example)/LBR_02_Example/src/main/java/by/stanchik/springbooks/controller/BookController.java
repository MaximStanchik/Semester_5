package by.stanchik.springbooks.controller;

import by.stanchik.springbooks.forms.BookForm;
import by.stanchik.springbooks.forms.EditBookForm;
import by.stanchik.springbooks.model.Book;
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
public class BookController {
    private static List<Book> books = new ArrayList<Book>();

    static {
        books.add(new Book("Full Stack Development with JHipster", "Deepu K Sasidharan, Sendil Kumar N"));
        books.add(new Book("Pro Spring Security", "Carlo Scarioni, Massimo Nardone"));
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

    @GetMapping(value = {"/allbooks"})
    public ModelAndView personList(Model model) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("booklist");
        model.addAttribute("books", books);
        return modelAndView;
    }

    @GetMapping(value = {"/addbook"})
    public  ModelAndView showAddPersonPage(Model model) {
        ModelAndView modelAndView = new ModelAndView("addbook");
        BookForm bookForm = new BookForm();
        model.addAttribute("bookform", bookForm);

        return modelAndView;
    }

    @GetMapping(value = {"/editbookinfo"})
    public ModelAndView showEditBookInfo(Model model) {
        ModelAndView modelAndView = new ModelAndView("editbookinfo");
        EditBookForm editBookForm = new EditBookForm();
        model.addAttribute("editbookinfo", editBookForm);
        return modelAndView;
    }

    @PostMapping("/deletebook/{index}")
    public String deleteBook(@PathVariable int index, Model model) {
        if (index >= 0 && index < books.size()) {
            books.remove(index);
        }
        model.addAttribute("books", books);
        return "redirect:/allbooks";
    }

    @PostMapping("/editbook/{index}")
    public String editBook(@PathVariable int index, Model model) {
        Book bookToEdit = books.get(index);
        EditBookForm editBookForm = new EditBookForm(String.valueOf(index), bookToEdit.getTitle(), bookToEdit.getAuthor());
        model.addAttribute("editBookForm", editBookForm);
        return "editbookinfo";
    }

    @PostMapping("/updatebook")
    public String updateBook(@ModelAttribute(name = "editBookInfo") EditBookForm editBookForm) {
        int index = Integer.parseInt(editBookForm.getIndex());
        if (index >= 0 && index < books.size()) {
            Book updatedBook = new Book(editBookForm.getTitle(), editBookForm.getAuthor());
            books.set(index, updatedBook);
        }
        return "redirect:/allbooks";
    }

    @PostMapping(value = {"/addbook"})
    public ModelAndView savePerson(Model model, @ModelAttribute("bookform") BookForm bookForm) {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("booklist");
        String title = bookForm.getTitle();
        String author = bookForm.getAuthor();

        if (title != null && title.length() > 0 //
                && author != null && author.length() > 0) {
            Book newBook = new Book(title, author);
            books.add(newBook);
            model.addAttribute("books",books);
            return modelAndView;
        }

        model.addAttribute("errorMessage", errorMessage);
        modelAndView.setViewName("addbook");
        return modelAndView;
    }

}

