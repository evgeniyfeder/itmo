package ru.ifmo.feder.rmi;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.Map;
import java.util.Set;

public class LocalPerson implements Person, Serializable {
    private String name, surname;
    private String pasportId;
    private Map<String, LocalAccount> accounts;

    LocalPerson(String name, String surname, String pasportId, Map<String, LocalAccount> accounts) {
        super();
        this.name = name;
        this.surname = surname;
        this.pasportId = pasportId;
        this.accounts = accounts;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getSurname() {
        return surname;
    }

    @Override
    public String getPasportId() {
        return pasportId;
    }

    Set<String> getAccounts() {
        return accounts.keySet();
    }

    Account getAccount(String accountId) {
        return accounts.get(accountId);
    }
}
