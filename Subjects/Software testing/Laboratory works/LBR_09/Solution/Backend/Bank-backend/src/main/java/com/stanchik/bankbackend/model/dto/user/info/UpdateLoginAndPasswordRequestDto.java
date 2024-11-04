package com.stanchik.bankbackend.model.dto.user.info;

public record UpdateLoginAndPasswordRequestDto(Long userId, String newLogin, String oldPassword, String newPassword) {
}
