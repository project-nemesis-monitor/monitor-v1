-- phpMyAdmin SQL Dump
-- version 5.2.1deb2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : jeu. 25 avr. 2024 à 10:53
-- Version du serveur : 10.11.6-MariaDB-2
-- Version de PHP : 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `nemesisbdd`
--

-- --------------------------------------------------------

--
-- Structure de la table `checkfile`
--

CREATE TABLE `checkfile` (
  `id` int(11) NOT NULL,
  `file_id` text NOT NULL,
  `filename` text NOT NULL,
  `check_mod` tinyint(1) NOT NULL,
  `path` text NOT NULL,
  `permissions` text DEFAULT NULL,
  `upload_by` text NOT NULL,
  `upload_at` timestamp NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Déchargement des données de la table `checkfile`
--

INSERT INTO `checkfile` (`id`, `file_id`, `filename`, `check_mod`, `path`, `permissions`, `upload_by`, `upload_at`) VALUES
(1, 'hhg4gg1', 'test2.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/testother/test2.txt', '644', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 05:37:31'),
(2, 'testbvh', 'xx.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/xx.txt', '666', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 05:37:37'),
(3, 'hhg4gg2', 'coucou.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/coucou.txt', '644', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 05:37:31');

-- --------------------------------------------------------

--
-- Structure de la table `logs`
--

CREATE TABLE `logs` (
  `id` int(11) NOT NULL,
  `operation` varchar(10) NOT NULL,
  `table_name` varchar(50) NOT NULL,
  `record_id` int(11) NOT NULL,
  `record_data` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL CHECK (json_valid(`record_data`)),
  `created_at` timestamp(3) NULL DEFAULT current_timestamp(3)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `user_id` text NOT NULL,
  `username` varchar(255) NOT NULL,
  `email` text NOT NULL,
  `role` varchar(255) NOT NULL,
  `password` text NOT NULL,
  `token` text NOT NULL,
  `remember_token` text DEFAULT NULL,
  `refresh_token_time` datetime DEFAULT NULL,
  `created_at` datetime(3) NOT NULL DEFAULT current_timestamp(3),
  `updated_at` datetime(3) DEFAULT current_timestamp(3)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Déchargement des données de la table `users`
--

INSERT INTO `users` (`id`, `user_id`, `username`, `email`, `role`, `password`, `token`, `remember_token`, `refresh_token_time`, `created_at`, `updated_at`) VALUES
(1, '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', 'root', 'root@example.com', 'super admin', '$2b$10$oJdQoaQaFSeO7oHeOk06VelqqBKDcWSbFBi3BPHJxm31J8SoH8Xma', 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOiIzMDFkMTI0Ni05M2JkLTRlN2YtYjU3MC1mZDdmYjJjNGQyYjEiLCJpYXQiOjE3MTE3MDI2Mzd9.YRDQTtJEVVffs6CMo63ke5e28REOQXTyJoNSJ6Pks5w', NULL, NULL, '2024-03-29 08:57:17.299', '2024-03-29 08:57:17.299');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `checkfile`
--
ALTER TABLE `checkfile`
  ADD PRIMARY KEY (`id`),
  ADD KEY `checkfile_upload_by_fkey` (`upload_by`(768));

--
-- Index pour la table `logs`
--
ALTER TABLE `logs`
  ADD PRIMARY KEY (`log_id`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `checkfile`
--
ALTER TABLE `checkfile`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pour la table `logs`
--
ALTER TABLE `logs`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT pour la table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;


DELIMITER //
CREATE TRIGGER `file_change_trigger` AFTER UPDATE ON `checkfile` FOR EACH ROW 
BEGIN
    INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('UPDATE', 'checkfile', NEW.id, JSON_OBJECT('file_id', NEW.file_id, 'filename', NEW.filename, 'check_mod', NEW.check_mod, 'path', NEW.path, 'permissions', NEW.permissions, 'upload_by', NEW.upload_by, 'upload_at', NEW.upload_at));
END       
//
DELIMITER ;   

DELIMITER //
CREATE TRIGGER `file_delete_trigger` AFTER DELETE ON `checkfile` FOR EACH ROW 
BEGIN
    INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('DELETE', 'checkfile', OLD.id, JSON_OBJECT('file_id', OLD.file_id, 'filename', OLD.filename, 'check_mod', OLD.check_mod, 'path', OLD.path, 'permissions', OLD.permissions, 'upload_by', OLD.upload_by, 'upload_at', OLD.upload_at)); 
END
//
DELIMITER ;

DELIMITER // 
CREATE TRIGGER `file_insert_trigger` AFTER INSERT ON `checkfile` FOR EACH ROW 
BEGIN
    INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('INSERT', 'checkfile', NEW.id, JSON_OBJECT('file_id', NEW.file_id, 'filename', NEW.filename, 'check_mod', NEW.check_mod, 'path', NEW.path, 'permissions', NEW.permissions, 'upload_by', NEW.upload_by, 'upload_at', NEW.upload_at)); 
END

//
DELIMITER ;

DELIMITER //
CREATE TRIGGER `after_user_delete_logs` AFTER DELETE ON `users`FOR EACH ROW 
BEGIN
	INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('DELETE', 'users', OLD.id, JSON_OBJECT('user_id', OLD.user_id, 'username', OLD.username, 'email', OLD.email, 'role', OLD.role, 'password', OLD.password, 'token', OLD.token, 'remember_token', OLD.remember_token, 'refresh_token_time', OLD.refresh_token_time, 'created_at', OLD.created_at, 'updated_at', OLD.updated_at));
END
//
DELIMITER ;
DELIMITER //
CREATE TRIGGER `after_user_insert_logs` AFTER INSERT ON `users`FOR EACH ROW 
BEGIN
	INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('INSERT', 'users', NEW.id, JSON_OBJECT('user_id', NEW.user_id, 'username', NEW.username, 'email', NEW.email, 'role', NEW.role, 'password', NEW.password, 'token', NEW.token, 'remember_token', NEW.remember_token, 'refresh_token_time', NEW.refresh_token_time, 'created_at', NEW.created_at, 'updated_at', NEW.updated_at));
END
//
DELIMITER ;
DELIMITER //
CREATE TRIGGER `after_user_update_logs` AFTER UPDATE ON `users`FOR EACH ROW 
BEGIN
	INSERT INTO logs (operation, table_name, record_id, record_data)
    VALUES ('UPDATE', 'users', NEW.id, JSON_OBJECT('user_id', NEW.user_id, 'username', NEW.username, 'email', NEW.email, 'role', NEW.role, 'password', NEW.password, 'token', NEW.token, 'remember_token', NEW.remember_token, 'refresh_token_time', NEW.refresh_token_time, 'created_at', NEW.created_at, 'updated_at', NEW.updated_at));
END
//
DELIMITER ;
