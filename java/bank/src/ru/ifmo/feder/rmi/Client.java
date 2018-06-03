package ru.ifmo.feder.rmi;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class Client {
    public static void main(final String... args) throws RemoteException {
        try {
            final Bank bank;
            try {
                bank = (Bank) Naming.lookup("//localhost/bank");
            } catch (final NotBoundException e) {
                System.out.println("Bank is not bound");
                return;
            } catch (final MalformedURLException e) {
                System.out.println("Bank URL is invalid");
                return;
            }

            String name, surname, passport, accountId;
            int change;

            try {
                name = args[0];
                surname = args[1];
                passport = args[2];
                accountId = args[3];
                change = Integer.parseInt(args[4]);
            } catch (Exception e) {
                System.out.println("ERROR: Wrong arguments format. Need <name> <surname> <passport> <account id> <change>");
                return;
            }

            Person person = bank.getRemotePerson(passport);
            if (person == null) {
                System.out.println("Creating new person");
                bank.createPerson(name, surname, passport);
            }

            if (!bank.getPersonAccounts(person).contains(accountId)) {
                System.out.println("Creating account");
                Account account = bank.getAccount(person, accountId);
                if (account != null) {
                    System.out.println("ERROR: Account already exists for another person!");
                    return;
                }
                bank.createAccount(person, accountId);
            }

            Account account = bank.getAccount(person, accountId);
            System.out.println("Account id: " + account.getId());
            System.out.println("Money: " + account.getAmount());
            System.out.println("Adding money");
            account.setAmount(account.getAmount() + change);
            System.out.println("Money: " + account.getAmount());

        } catch (RemoteException e) {
            System.out.println("ERROR: Problems with remote." + e);
        }
    }
}
