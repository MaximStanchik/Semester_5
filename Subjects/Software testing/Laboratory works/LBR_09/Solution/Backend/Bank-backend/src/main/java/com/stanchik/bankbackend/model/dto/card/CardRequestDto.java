package com.stanchik.bankbackend.model.dto.card;

public record CardRequestDto(Long accountId, String type, String cardName,
                             String description, String status
)
{

}
