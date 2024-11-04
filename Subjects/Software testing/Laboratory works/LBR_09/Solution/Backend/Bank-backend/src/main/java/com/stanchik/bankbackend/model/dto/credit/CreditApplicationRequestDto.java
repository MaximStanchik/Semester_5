package com.stanchik.bankbackend.model.dto.credit;

import java.math.BigDecimal;

public record CreditApplicationRequestDto(Long creditTypeId, Long accountId, BigDecimal amount) {
}
