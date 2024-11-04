package com.stanchik.bankbackend.service;

import com.stanchik.bankbackend.model.User;
import com.stanchik.bankbackend.model.dto.user.info.UpdateLoginAndPasswordRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginRequestDto;
import com.stanchik.bankbackend.model.dto.user.login.LoginResponseDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserRequestDto;
import com.stanchik.bankbackend.model.dto.user.registration.RegisterUserResponseDto;
import com.stanchik.bankbackend.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.util.Streamable;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.SqlOutParameter;
import org.springframework.jdbc.core.SqlParameter;
import org.springframework.jdbc.core.simple.SimpleJdbcCall;
import org.springframework.stereotype.Service;

import java.security.SecureRandom;
import java.sql.Types;
import java.util.*;

@Service
public class UserService {
    private final JdbcTemplate jdbcTemplate;
    private SimpleJdbcCall registerUserCall;

    public UserRepository userRepository;

    @Autowired
    public UserService(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
        this.registerUserCall = new SimpleJdbcCall(jdbcTemplate)
                .withProcedureName("REGISTER_USER")
                .declareParameters(
                        new SqlParameter("p_login", Types.VARCHAR),
                        new SqlParameter("p_password", Types.VARCHAR),
                        new SqlOutParameter("p_user_id", Types.NUMERIC),
                        new SqlOutParameter("p_user_login", Types.VARCHAR)
                );
    }

    public RegisterUserResponseDto registerUser(RegisterUserRequestDto registerUserRequestDto) {
        Map<String, Object> params = new HashMap<>();
        params.put("p_login", registerUserRequestDto.login());
        params.put("p_password", registerUserRequestDto.password());

        Map<String, Object> result = registerUserCall.execute(params);

        Number userId = (Number) result.get("p_user_id");
        String userLogin = (String) result.get("p_user_login");

        return new RegisterUserResponseDto(userId.longValue(), userLogin);
    }

    private static final SecureRandom secureRandom = new SecureRandom(); //threadsafe
    private static final Base64.Encoder base64Encoder = Base64.getUrlEncoder(); //threadsafe

    public RegisterUserResponseDto register (RegisterUserRequestDto requestDto) {

        userRepository.findByLogin(requestDto.login())
                .map(user -> {throw new RuntimeException("user already exists");});

        if (!validateUserInput(requestDto.login(), requestDto.password())) {
            throw new RuntimeException("Login or password are not valid");
        }
        else {
            User user = userRepository.save(new User(null, requestDto.login(), requestDto.password(), new ArrayList<>()));
            return new RegisterUserResponseDto(user.getId(), user.getLogin());
        }
    }

    public boolean validateUserInput (String login, String password) {
        if (!login.matches("[a-zA-Z0-9]{2,255}") || !password.matches("[a-zA-Z0-9%!\\-:;]{2,255}")) {
            return false;
        }
        else {
            return true;
        }
    }

    public static String generateNewToken() {
        byte[] randomBytes = new byte[24];
        secureRandom.nextBytes(randomBytes);
        return base64Encoder.encodeToString(randomBytes);
    }

    public LoginResponseDto login (LoginRequestDto requestDto) {

        return userRepository.findByLogin(requestDto.login()).map(user -> {
            if (user.getPassword().equals(requestDto.password())) {
                return new LoginResponseDto(user.getId(), generateNewToken());
            }
            else {
                throw new RuntimeException("User password doesn't match");
            }
        }).orElseThrow();

    }

    public void updateUser(UpdateLoginAndPasswordRequestDto requestDto) {
        userRepository.findById(requestDto.userId()).map(user -> {
            if (user.getPassword().equals(requestDto.oldPassword())) {
                user.setLogin(requestDto.newLogin());
                user.setPassword(requestDto.newPassword());
                return userRepository.save(user);
            }
            else {
                throw new RuntimeException("User password doesn't match");
            }
        }).orElseThrow(() -> new RuntimeException("User not found"));
    }

    public List<User> getAll() {
        return Streamable.of(userRepository.findAll()).toList();
    }

}