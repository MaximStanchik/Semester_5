package com.stanchik.bankbackend.model.dto.transaction;

import java.math.BigDecimal;
import java.time.LocalDateTime;

public record CreateTransactionRequestDto(Long accountIdFrom, Long accountIdTo, BigDecimal amount, LocalDateTime dateTime) {

};
