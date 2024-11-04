package com.stanchik.bankbackend.model.dto.payment;

public record PaymentServiceDto(Long id, String name, String type, Long transactionId) {
}
