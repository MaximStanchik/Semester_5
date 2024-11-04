package com.stanchik.bankbackend.model.dto.account;

public record CreateAccountRequestDto(Long userId, String name, String currency) {

}
