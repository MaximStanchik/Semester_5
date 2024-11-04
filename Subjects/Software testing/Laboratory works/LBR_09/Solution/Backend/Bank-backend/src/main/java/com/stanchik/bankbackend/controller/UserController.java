package com.stanchik.bankbackend.controller;

import com.stanchik.bankbackend.model.User;
import com.stanchik.bankbackend.model.dto.user.info.UpdateLoginAndPasswordRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginResponseDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserRequestDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserResponseDto;
import com.stanchik.bankbackend.service.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RequiredArgsConstructor
@RequestMapping("/users")
@RestController
public class UserController {
    private final UserService userService;
    @PostMapping("/register")
    public ResponseEntity<RegisterUserResponseDto> register (@RequestBody RegisterUserRequestDto registerUserRequestDto) {
        return ResponseEntity.ok(userService.registerUser(registerUserRequestDto));
    };

    @PostMapping("/login")
    public ResponseEntity<LoginResponseDto> login (@RequestBody LoginRequestDto loginRequestDto) {
        return ResponseEntity.ok(userService.login(loginRequestDto));
    };
    @PutMapping ("")
    public ResponseEntity<Void> updateUserInfo (@RequestBody UpdateLoginAndPasswordRequestDto loginRequestDto) {
        userService.updateUser(loginRequestDto);
        return ResponseEntity.ok().build();
    };

    @GetMapping()
    public ResponseEntity<List<User>> getAllUsers () {
        return ResponseEntity.ok(userService.getAll());
    }

};
