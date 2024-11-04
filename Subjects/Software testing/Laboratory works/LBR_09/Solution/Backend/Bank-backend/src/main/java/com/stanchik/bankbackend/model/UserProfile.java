package com.stanchik.bankbackend.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.util.Date;

@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
public class UserProfile {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @OneToOne
    @JoinColumn(name = "USER_ID", referencedColumnName = "ID", nullable = false)
    private User userId;

    @Column(name = "FIRST_NAME", length = 50, nullable = false)
    private String firstName;

    @Column(name = "LAST_NAME", length = 50, nullable = false)
    private String lastName;

    @Column(name = "MIDDLE_NAME", length = 50)
    private String middleName;

    @Column(name = "ADDRESS")
    private String address;

    @Column(name = "BIRTH_DATE")
    private Date birthDate;

    @Column(name = "EMAIL", length = 100)
    private String email;

    @Column(name = "PASSPORT_NUM", length = 20, nullable = false)
    private String passportNum;

    @Column(name = "PHONE_NUMBER", length = 50)
    private String phoneNumber;

}
