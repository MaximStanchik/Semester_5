package com.stanchik.bankbackend.config;

import jakarta.annotation.PostConstruct;
import lombok.RequiredArgsConstructor;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

@Component
@RequiredArgsConstructor
public class DbInitConfig {
    private final JdbcTemplate jdbcTemplate;

    @PostConstruct
    public void init() {
        createStoredProcedures();
    }

    private void createStoredProcedures() {
        String sql = readSqlFromFile("sql/RegisterUser.sql");

        if (sql != null) {
            jdbcTemplate.execute(sql);
        }
        else {
            throw new RuntimeException("SQL script could not be read.");
        }
    }

    private String readSqlFromFile(String filename) {
        StringBuilder sqlBuilder = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(
                getClass().getClassLoader().getResourceAsStream(filename), StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null) {
                sqlBuilder.append(line).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return sqlBuilder.toString();
    }
}

