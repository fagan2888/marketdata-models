-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Dim 10 Mai 2015 à 22:43
-- Version du serveur: 5.5.24-log
-- Version de PHP: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `marketdata`
CREATE DATABASE IF NOT EXISTS marketdata;
use marketdata;
--

-- --------------------------------------------------------

--
-- Structure de la table `market_data`
--

DROP TABLE IF EXISTS `market_data`;
CREATE TABLE IF NOT EXISTS `market_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `symbol` varchar(20) NOT NULL,
  `price` varchar(10) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=123582 ;




-- --------------------------------------------------------

--
-- Structure de la table `taux_euribor`
--

DROP TABLE IF EXISTS `taux_euribor`;
CREATE TABLE IF NOT EXISTS `taux_euribor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `valeur` varchar(15) DEFAULT NULL,
  `periode` varchar(15) DEFAULT NULL,
  `date` date NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;


--
-- Contenu de la table `taux_euribor`
--

INSERT INTO `taux_euribor` (`id`, `valeur`, `periode`, `date`) VALUES
(1, '-0.00107', '1', '2015-05-08'),
(2, '-0.00091', '2', '2015-05-08'),
(3, '-0.00044', '4', '2015-05-08'),
(4, '-0.00025', '8', '2015-05-08'),
(5, '-0.00009', '12', '2015-05-08'),
(6, '0.00061', '24', '2015-05-08'),
(7, '0.00108', '36', '2015-05-08'),
(8, '0.00169', '48', '2015-05-08');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;


