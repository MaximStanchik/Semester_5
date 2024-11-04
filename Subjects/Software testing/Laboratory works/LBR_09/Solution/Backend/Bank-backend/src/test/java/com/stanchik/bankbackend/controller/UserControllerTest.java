package com.stanchik.bankbackend.controller;

import com.stanchik.bankbackend.model.User;
import com.stanchik.bankbackend.model.dto.user.info.UpdateLoginAndPasswordRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginResponseDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserRequestDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserResponseDto;
import com.stanchik.bankbackend.service.UserService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.http.ResponseEntity;
import static org.mockito.Mockito.*;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class UserControllerTest {
    @Mock
    private UserService userService;

    @InjectMocks
    private UserController userController;

    @BeforeEach
    public void setUp() {
        MockitoAnnotations.openMocks(this);
    }

    @Test
    public void testRegister() {
        RegisterUserRequestDto requestDto = new RegisterUserRequestDto("testUser", "password");
        RegisterUserResponseDto responseDto = new RegisterUserResponseDto(1L, "testUser");

        when(userService.registerUser(any(RegisterUserRequestDto.class))).thenReturn(responseDto);

        ResponseEntity<RegisterUserResponseDto> response = userController.register(requestDto);

        assertEquals(200, response.getStatusCodeValue());
        assertEquals(responseDto, response.getBody());

        verify(userService, times(1)).registerUser(requestDto);
    }

    @Test
    public void testLogin() {
        LoginRequestDto requestDto = new LoginRequestDto("testUser", "password");

        LoginResponseDto responseDto = new LoginResponseDto(1L, "token");

        when(userService.login(requestDto)).thenReturn(responseDto);

        ResponseEntity<LoginResponseDto> response = userController.login(requestDto);

        assertEquals(200, response.getStatusCodeValue());

        assertEquals(responseDto, response.getBody());

        verify(userService, times(1)).login(requestDto);
    }

    @Test
    public void testUpdateUserInfo() {
        UpdateLoginAndPasswordRequestDto requestDto = new UpdateLoginAndPasswordRequestDto(1L, "oldPassword", "newUser", "newPassword");

        ResponseEntity<Void> response = userController.updateUserInfo(requestDto);

        assertEquals(200, response.getStatusCodeValue());
        verify(userService, times(1)).updateUser(requestDto);
    }

    @Test
    public void testGetAllUsers() {
        List<User> users = new ArrayList<>();
        users.add(new User(1L, "testUser", "password", null));

        when(userService.getAll()).thenReturn(users);

        ResponseEntity<List<User>> response = userController.getAllUsers();

        assertEquals(200, response.getStatusCodeValue());
        assertEquals(users, response.getBody());
        verify(userService, times(1)).getAll();
    }
}
