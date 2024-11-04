package com.stanchik.bankbackend.model.dto.rate;

import java.math.BigDecimal;
import java.time.LocalDate;

public record ExchangeRateRequestDto(Long sourceCurrId, Long targetCurrId, BigDecimal rate, LocalDate date) {
}
